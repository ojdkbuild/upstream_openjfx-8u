/*
 * Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

package javafx.scene.control;

/**
Builder class for javafx.scene.control.ScrollPane
@see javafx.scene.control.ScrollPane
@deprecated This class is deprecated and will be removed in the next version
* @since JavaFX 2.0
*/
@javax.annotation.Generated("Generated by javafx.builder.processor.BuilderProcessor")
@Deprecated
public class ScrollPaneBuilder<B extends javafx.scene.control.ScrollPaneBuilder<B>> extends javafx.scene.control.ControlBuilder<B> implements javafx.util.Builder<javafx.scene.control.ScrollPane> {
    protected ScrollPaneBuilder() {
    }

    /** Creates a new instance of ScrollPaneBuilder. */
    @SuppressWarnings({"deprecation", "rawtypes", "unchecked"})
    public static javafx.scene.control.ScrollPaneBuilder<?> create() {
        return new javafx.scene.control.ScrollPaneBuilder();
    }

    private int __set;
    private void __set(int i) {
        __set |= 1 << i;
    }
    public void applyTo(javafx.scene.control.ScrollPane x) {
        super.applyTo(x);
        int set = __set;
        while (set != 0) {
            int i = Integer.numberOfTrailingZeros(set);
            set &= ~(1 << i);
            switch (i) {
                case 0: x.setContent(this.content); break;
                case 1: x.setFitToHeight(this.fitToHeight); break;
                case 2: x.setFitToWidth(this.fitToWidth); break;
                case 3: x.setHbarPolicy(this.hbarPolicy); break;
                case 4: x.setHmax(this.hmax); break;
                case 5: x.setHmin(this.hmin); break;
                case 6: x.setHvalue(this.hvalue); break;
                case 7: x.setPannable(this.pannable); break;
                case 8: x.setPrefViewportHeight(this.prefViewportHeight); break;
                case 9: x.setPrefViewportWidth(this.prefViewportWidth); break;
                case 10: x.setVbarPolicy(this.vbarPolicy); break;
                case 11: x.setViewportBounds(this.viewportBounds); break;
                case 12: x.setVmax(this.vmax); break;
                case 13: x.setVmin(this.vmin); break;
                case 14: x.setVvalue(this.vvalue); break;
            }
        }
    }

    private javafx.scene.Node content;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getContent() content} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B content(javafx.scene.Node x) {
        this.content = x;
        __set(0);
        return (B) this;
    }

    private boolean fitToHeight;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#isFitToHeight() fitToHeight} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B fitToHeight(boolean x) {
        this.fitToHeight = x;
        __set(1);
        return (B) this;
    }

    private boolean fitToWidth;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#isFitToWidth() fitToWidth} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B fitToWidth(boolean x) {
        this.fitToWidth = x;
        __set(2);
        return (B) this;
    }

    private javafx.scene.control.ScrollPane.ScrollBarPolicy hbarPolicy;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getHbarPolicy() hbarPolicy} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B hbarPolicy(javafx.scene.control.ScrollPane.ScrollBarPolicy x) {
        this.hbarPolicy = x;
        __set(3);
        return (B) this;
    }

    private double hmax;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getHmax() hmax} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B hmax(double x) {
        this.hmax = x;
        __set(4);
        return (B) this;
    }

    private double hmin;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getHmin() hmin} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B hmin(double x) {
        this.hmin = x;
        __set(5);
        return (B) this;
    }

    private double hvalue;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getHvalue() hvalue} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B hvalue(double x) {
        this.hvalue = x;
        __set(6);
        return (B) this;
    }

    private boolean pannable;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#isPannable() pannable} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B pannable(boolean x) {
        this.pannable = x;
        __set(7);
        return (B) this;
    }

    private double prefViewportHeight;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getPrefViewportHeight() prefViewportHeight} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B prefViewportHeight(double x) {
        this.prefViewportHeight = x;
        __set(8);
        return (B) this;
    }

    private double prefViewportWidth;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getPrefViewportWidth() prefViewportWidth} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B prefViewportWidth(double x) {
        this.prefViewportWidth = x;
        __set(9);
        return (B) this;
    }

    private javafx.scene.control.ScrollPane.ScrollBarPolicy vbarPolicy;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getVbarPolicy() vbarPolicy} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B vbarPolicy(javafx.scene.control.ScrollPane.ScrollBarPolicy x) {
        this.vbarPolicy = x;
        __set(10);
        return (B) this;
    }

    private javafx.geometry.Bounds viewportBounds;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getViewportBounds() viewportBounds} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B viewportBounds(javafx.geometry.Bounds x) {
        this.viewportBounds = x;
        __set(11);
        return (B) this;
    }

    private double vmax;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getVmax() vmax} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B vmax(double x) {
        this.vmax = x;
        __set(12);
        return (B) this;
    }

    private double vmin;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getVmin() vmin} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B vmin(double x) {
        this.vmin = x;
        __set(13);
        return (B) this;
    }

    private double vvalue;
    /**
    Set the value of the {@link javafx.scene.control.ScrollPane#getVvalue() vvalue} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B vvalue(double x) {
        this.vvalue = x;
        __set(14);
        return (B) this;
    }

    /**
    Make an instance of {@link javafx.scene.control.ScrollPane} based on the properties set on this builder.
    */
    public javafx.scene.control.ScrollPane build() {
        javafx.scene.control.ScrollPane x = new javafx.scene.control.ScrollPane();
        applyTo(x);
        return x;
    }
}
