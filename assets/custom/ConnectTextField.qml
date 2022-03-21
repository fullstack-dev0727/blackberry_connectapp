import bb.cascades 1.4

TextField {
     textStyle.base:  myStyle.style
     
     attachedObjects: [
         ConnectTextStyle {
             id: myStyle
         }
     ]
}

