// Copyright 2017 The Lynx Authors. All rights reserved.
package com.lynx.base;

public class Position {
    public int mLeft;
    public int mTop;
    public int mRight;
    public int mBottom;

    public Position() {
        this.mLeft = 0;
        this.mTop = 0;
        this.mRight = 0;
        this.mBottom = 0;
    }

    public Position(int left, int top, int right, int bottom) {
        this.mLeft = left;
        this.mTop = top;
        this.mRight = right;
        this.mBottom = bottom;
    }

    public int getWidth() { return  mRight - mLeft; }

    public int getHeight() { return  mBottom- mTop; }
}
