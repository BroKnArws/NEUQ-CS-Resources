package com.strutnut.bean;

import java.io.Serializable;
import java.util.List;

public class ObjectClazz implements Serializable {

    private byte[] classContent;
    private List<String> methodNames;

    public byte[] getClassContent() {
        return classContent;
    }

    public void setClassContent(byte[] classContent) {
        this.classContent = classContent;
    }

    public List<String> getMethodNames() {
        return methodNames;
    }

    public void setMethodNames(List<String> methodNames) {
        this.methodNames = methodNames;
    }
}
