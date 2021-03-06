// Copyright 2017 The Lynx Authors. All rights reserved.

#include "render/render_tree_host.h"

#include "render/impl/render_command.h"
#include "render/render_object.h"
#include "render/render_tree_host_impl.h"
#include "runtime/canvas.h"
#include "runtime/element.h"
#include "runtime/runtime.h"

#include "base/trace_event/trace_event_common.h"

namespace lynx {

RenderTreeHost::RenderTreeHost(jscore::JSContext* context,
                               jscore::ThreadManager* thread_manager,
                               RenderObject* root)
    : collector_(),
      context_(context),
      thread_manager_(thread_manager),
      did_first_layout_(false),
      page_location_("") {
  SetRenderRoot(root);
}

RenderTreeHost::~RenderTreeHost() {
}

void RenderTreeHost::SetRenderRoot(RenderObject* root) {
  render_root_ = root;
  if (render_root_ == NULL)
    return;
  render_tree_host_impl_ = RenderTreeHostImpl::Create(thread_manager_, this,
                                                        render_root_->impl());
}

void RenderTreeHost::UpdateRenderObject(RenderCommand* command) {
  // exec command immediately
  thread_manager_->RunOnUIThread(command);

  // collect command and wait vsync signal to exec
  // collector_.Collect(command);
}

void RenderTreeHost::ForceLayout(int left, int top, int right, int bottom) {
  render_root_->ReLayout(left, top, right, bottom);
}

void RenderTreeHost::DoBeginFrame(const BeginFrameData& data) {
  viewport_ = data.viewport_;
  PrepareCommit(data);
  render_root_->ReLayout(viewport_.left_, viewport_.top_, viewport_.right_,
                         viewport_.bottom_);
  render_tree_host_impl_->NotifyBeginFrameComplete();
}

void RenderTreeHost::PrepareCommit(const BeginFrameData& data) {
  render_tree_host_impl_->PrepareCommit();
  collector_.Push();
}

void RenderTreeHost::DoCommit() {
  TRACE_EVENT0("renderer", "RenderTreeHost::DoCommit");
  RenderCommandCollector::RenderCommands* commands = collector_.Pop();
  if (commands == NULL)
    return;
  RenderCommandCollector::RenderCommandsStorage::iterator iter =
      commands->begin();
  for (; iter != commands->end(); ++iter) {
    (*iter)->Execute();
  }
  lynx_delete(commands);
}

void RenderTreeHost::ForceFlushCommands() {
  TRACE_EVENT0("js", "RenderTreeHost::ForceFlushCommands");
  collector_.Push();
  DoCommit();
}

void RenderTreeHost::TreeSync() {
  {
    TRACE_EVENT0("js", "RenderTreeHost::TreeSync");
    RendererSync(render_root());
  }
  context_->runtime()->FlushScript();
}

void RenderTreeHost::RendererSync(RenderObject* renderer) {
  RenderObject* child = static_cast<RenderObject*>(renderer->FirstChild());
  while (child) {
    if (!child->IsPrivate()) {
      jscore::Element* element = NULL;
      if (child->IsCanvas()) {
        element = lynx_new jscore::Canvas(context_, child);
      } else {
        element = lynx_new jscore::Element(context_, child);
      }
      jscore::Element::ProtectChild(context_, element);
    }
    RendererSync(child);
    child = static_cast<RenderObject*>(child->Next());
  }
}

}  // namespace lynx
