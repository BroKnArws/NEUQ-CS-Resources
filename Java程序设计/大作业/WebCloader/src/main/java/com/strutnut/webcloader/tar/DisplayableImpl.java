package com.strutnut.webcloader.tar;


import com.strutnut.annotation.ObjectClass;
import com.strutnut.annotation.ObjectMethod;

@ObjectClass
public class DisplayableImpl implements Displayable {

    @Override
    @ObjectMethod
    public void display() {
        System.out.println("Can I think in the future?");
    }

    @ObjectMethod
    public void next() {
        System.out.println("Every Dream Will Come True.");
    }
}
