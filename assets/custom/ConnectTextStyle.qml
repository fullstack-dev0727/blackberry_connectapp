import bb.cascades 1.4

 TextStyleDefinition {
     id: myRegularStyle
     base: SystemDefaults.TextStyles.BodyText
     
     rules: [
         FontFaceRule {
             source: "asset:///fonts/robotoregular.ttf"
             fontFamily: "ConnectFontRegular"
         }
     ]
     fontFamily: "ConnectFontRegular, sans-serif"
 }
    
