import bb.cascades 1.4

Label {
     textStyle.base:  myStyle.style
     textFormat: TextFormat.Html
     
     attachedObjects: [
         ConnectTextStyle {
             id: myStyle
         }
     ]
}

