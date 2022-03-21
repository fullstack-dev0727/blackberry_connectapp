import bb.cascades 1.4

Dialog {
    id: pinDialog
    Container {
        
        verticalAlignment: VerticalAlignment.Fill
        horizontalAlignment: HorizontalAlignment.Fill
        
        layout: DockLayout {
        
        }
        background: Color.create("#ffffffff")
        Container {
            horizontalAlignment: HorizontalAlignment.Center
            ImageView {
                imageSource: "asset:///images/img/pin_ic_header.png"
                horizontalAlignment: HorizontalAlignment.Center
                preferredWidth: 467.0
                preferredHeight: 117.0
                scalingMethod: ScalingMethod.AspectFill
                margin.topOffset: 100.0
            }
            Label {
                text: "Please enter your Pin\n"
                horizontalAlignment: HorizontalAlignment.Center
                textFit.maxFontSizeValue: 8.0
                textStyle.color: Color.create("#ff646464")
                margin.topOffset: 50.0
            }
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                margin.topOffset: 20.0
                layout: GridLayout {
                    columnCount: 4
                }
                ImageView {
                    id: pin1
                    imageSource: "asset:///images/img/pin_deselected.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: 120.0
                    preferredHeight: 120.0
                    scalingMethod: ScalingMethod.AspectFill
                    margin.leftOffset: 10.0
                    margin.rightOffset: 10.0
                }
                ImageView {
                    id: pin2
                    imageSource: "asset:///images/img/pin_deselected.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: 120.0
                    preferredHeight: 120.0
                    scalingMethod: ScalingMethod.AspectFill
                    margin.leftOffset: 10.0
                    margin.rightOffset: 10.0
                }
                ImageView {
                    id: pin3
                    imageSource: "asset:///images/img/pin_deselected.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: 120.0
                    preferredHeight: 120.0
                    scalingMethod: ScalingMethod.AspectFill
                    margin.rightOffset: 10.0
                    margin.leftOffset: 10.0
                }
                ImageView {
                    id: pin4
                    imageSource: "asset:///images/img/pin_deselected.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: 120.0
                    preferredHeight: 120.0
                    scalingMethod: ScalingMethod.AspectFill
                    margin.rightOffset: 10.0
                    margin.leftOffset: 10.0
                }
            }
        }
        Container {
            
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Bottom
            Container {
                layout: GridLayout {
                    columnCount: 3
                
                }
                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Fill
                background: Color.create("#fff0f0f0")
                Container {
                    ImageView {
                        id: key1
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("1");
                        }
                    }
                    
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                    Label {
                        text: "1"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                }
                Container {
                    ImageView {
                        id: key2
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("2");
                        }
                    }
                    Label {
                        text: "2"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key3
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("3");
                        }
                    }
                    Label {
                        text: "3"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key4
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("4");
                        }
                    }
                    Label {
                        text: "4"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key5
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("5");
                        }
                    }
                    Label {
                        text: "5"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key6
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("6");
                        }
                    }
                    Label {
                        text: "6" 
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key7
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("7");
                        }
                    }
                    Label {
                        text: "7"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key8
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("8");
                        }
                    }
                    Label {
                        text: "8"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key9
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("9");
                        }
                    }
                    Label {
                        text: "9" 
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        scalingMethod: ScalingMethod.Fill
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key0
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        imageSource: "asset:///images/img/key_normal.png"
                        scalingMethod: ScalingMethod.Fill
                        onTouch: {
                            pinDialog1.addNumber("0");
                        }
                    }
                    Label {
                        text: "0"
                        textStyle.textAlign: TextAlign.Center
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        textFit.maxFontSizeValue: 12.0
                        textFit.minFontSizeValue: 12.0
                        textStyle.color: Color.create("#aa537984")
                        margin.topOffset: 15.0
                        margin.bottomOffset: 15.0
                    }
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
                Container {
                    ImageView {
                        id: key_delete
                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        scalingMethod: ScalingMethod.AspectFit
                        imageSource: "asset:///images/img/pin_delete.png"
                        onTouch: {
                            pinDialog1.deleteNumber();
                        }
                    
                    }
                    
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    layout: DockLayout {
                    
                    }
                }
            }
        
        }
    
    }

}