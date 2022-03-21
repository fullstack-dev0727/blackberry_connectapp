import bb.cascades 1.4

TextArea {
     textStyle.base:  myStyle.style
     
     attachedObjects: [
         ConnectTextStyle {
             id: myStyle
         }
     ]
}

