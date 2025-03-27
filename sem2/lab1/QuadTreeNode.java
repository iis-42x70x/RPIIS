package com.example.test;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class QuadTreeNode {
    private final int capacity = 4;
    private int value;
    private boolean isLeaf;
    private QuadTreeNode topRight;
    private QuadTreeNode topLeft;
    private QuadTreeNode bottomRight;
    private QuadTreeNode bottomLeft;

    public QuadTreeNode() {
        this.isLeaf = false;
    }


}
