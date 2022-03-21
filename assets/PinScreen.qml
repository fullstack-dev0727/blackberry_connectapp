import bb.cascades 1.4

Dialog {
    id: pinDialog
    Container {
        layout: AbsoluteLayout {

        }
        
        ImageView {
            id: backgroundImageView
            minHeight: 400
            minWidth: 718
            maxHeight: 400
            maxWidth: 718
            imageSource: "asset:///images/img/pin_background.png"
        }
        Container {
            topPadding: 80
            minHeight: 400
            minWidth: 718
            maxHeight: 400
            maxWidth: 718
            layout: StackLayout {
                
            }
            Label {
                // Localized text with the dynamic translation and locale updates support
                text: qsTr("Please enter your Pin") + Retranslate.onLocaleOrLanguageChanged
                textStyle.base: SystemDefaults.TextStyles.BigText
                textStyle.color: Color.White
                horizontalAlignment: HorizontalAlignment.Center
                textStyle.fontWeight: FontWeight.Default
                textStyle.fontStyle: FontStyle.Normal
                textStyle.textAlign: TextAlign.Center
                textStyle.fontSize: FontSize.XLarge
            }
            
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                
                }
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                
                topMargin: 50.0
                TextField {
                    text: ""
                    hintText: ""
                    inputMode: TextFieldInputMode.Pin
                    input.submitKey: SubmitKey.Done
                    input.keyLayout: KeyLayout.Pin
                    textStyle.textAlign: TextAlign.Center
                    textStyle.color: Color.Black
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center

                    maxWidth: 500.0
                    minWidth: 500.0

                }

            }
        }

    }
}