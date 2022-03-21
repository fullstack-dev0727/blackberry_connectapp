import bb.cascades 1.4
import bb.device 1.4
import bb.system 1.2
import "../DetailScreens"
import "../custom"

Page {

    function informUserAndClose() {
        loadingDialog.close();
        _home.popScreen();
        myQmlToast.show();

    }

    function closeScreen() {
        _main.popScreen();
    }

    onCreationCompleted: {
        _control.ctMessageSent.connect(closeScreen)
    }

    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        onTouch: {
            _control.onTouchFunc();
        }
        Container {
            preferredHeight: ui.sdu(14)
            background: Color.create("#1978bb")
            horizontalAlignment: HorizontalAlignment.Fill
            layout: DockLayout {
            }

            ConnectLabel {
                text: "Household Details"
                textStyle.color: Color.White
                textStyle.fontSize: FontSize.Small
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center

            }
        }

        Container {
            layout: DockLayout {

            }
            visible: typeof _control.m_ContactInfo.Email === 'undefined' ? false : true
 
            ScrollView {
                Container {
                    verticalAlignment: VerticalAlignment.Top
                    layout: StackLayout {
                        orientation: LayoutOrientation.TopToBottom
                    }

                    Container {
                        visible: _control.error
                        layout: StackLayout {
                            orientation: LayoutOrientation.TopToBottom
                        }
                        margin.topOffset: ui.sdu(10)
                        horizontalAlignment: HorizontalAlignment.Fill

                        ImageView {
                            imageSource: "asset:///images/img/icon_warning.png"
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center
                        }

                        Label {
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center
                            multiline: true
                            margin.leftOffset: ui.sdu(5)
                            margin.rightOffset: ui.sdu(5)

                            text: _control.errorMessage
                            textStyle {
                                base: SystemDefaults.TextStyles.PrimaryText
                                color: Color.DarkGray
                                textAlign: TextAlign.Center
                            }

                        }
                    }

                    Container {

                        preferredHeight: ui.sdu(80)
                        horizontalAlignment: HorizontalAlignment.Fill

                        layout: DockLayout {

                        }

                        Container {
                            verticalAlignment: VerticalAlignment.Fill
                            horizontalAlignment: HorizontalAlignment.Fill

                            layout: StackLayout {
                                orientation: LayoutOrientation.TopToBottom
                            }

                            Container {
                                background: Color.create("#FF2F66B7") //blue
                                horizontalAlignment: HorizontalAlignment.Fill
                                preferredWidth: maxWidth

                                id: mainPhoto

                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1
                                }

                                Container {

                                    layout: DockLayout {

                                    }

                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    preferredHeight: mainPhoto.maxHeight

                                    ScrollView {

                                        id: gestureContainer
                                        scrollViewProperties {
                                            scrollMode: ScrollMode.Both
                                        }
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Fill

                                        scrollRole: ScrollRole.Main
                                        scrollViewProperties.minContentScale: 1.0
                                        scrollViewProperties.maxContentScale: 8.0
                                        scrollViewProperties.pinchToZoomEnabled: true
                                        scrollViewProperties.overScrollEffectMode: OverScrollEffectMode.Default

                                        // The ImageView that shows the loaded image after loading has finished without error
                                        ImageView {
                                            id: topImage
                                            scalingMethod: ScalingMethod.Fill
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill

                                            image: _control.myDetails.image
                                            visible: ! _control.myDetails.loading && _control.myDetails.label == ""
                                        }
                                    }

                                    // The ImageView that shows the loaded image after loading has finished with error or there is no image
                                    ImageView {
                                        id: notopImage
                                        scalingMethod: ScalingMethod.AspectFit
                                        horizontalAlignment: HorizontalAlignment.Center
                                        verticalAlignment: VerticalAlignment.Center

                                        imageSource: "asset:///images/img/no_image.png"
                                        visible: ! _control.myDetails.loading && _control.myDetails.label != ""
                                    }

                                }

                            }

                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                layout: DockLayout {
                                    //orientation: LayoutOrientation.TopToBottom
                                }

                                id: mainContent

                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1
                                }

                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.TopToBottom
                                    }

                                    margin.topOffset: ui.sdu(12)
                                    margin.leftOffset: ui.sdu(8)
                                    margin.rightOffset: ui.sdu(8)
                                    verticalAlignment: VerticalAlignment.Top
                                    horizontalAlignment: HorizontalAlignment.Center

                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Center
                                        textStyle.fontSize: FontSize.Large
                                        textStyle.color: Color.create("#FF37474F")

                                        text: _control.myDetails.itemData.LastName + ", " + _control.myDetails.itemData.FirstName
                                        multiline: true
                                    }

                                    Container {
                                        id: btContainer
                                        layout: DockLayout {

                                        }
                                        horizontalAlignment: HorizontalAlignment.Center
                                        preferredHeight: ui.sdu(10)
                                        margin.topOffset: ui.sdu(4)

                                        ImageView {
                                            imageSource: "asset:///images/nineslice/rounded.amd"
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill
                                            filterColor: Color.create("#FF2F66B7")
                                        }

                                        ConnectLabel {
                                            horizontalAlignment: HorizontalAlignment.Center
                                            verticalAlignment: VerticalAlignment.Center
                                            textStyle.fontSize: FontSize.Medium
                                            textStyle.color: Color.White

                                            text: "   Manage subscription   "

                                            onTouch: {
                                                if (event.touchType == TouchType.Down) {
                                                    //Do something on down touch - e.g. change background color
                                                } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                                                    //Users finger has been lifted OR has left the element.
                                                    onClicked:
                                                    {
                                                        _control.manageSubs();
                                                    }
                                                }
                                            }

                                        }

                                    }

                                }

                                //ConnectLabel {
                                //     text: "Household Info"
                                //     verticalAlignment: VerticalAlignment.Bottom
                                //      horizontalAlignment: HorizontalAlignment.Left

                                //       textStyle.color: Color.create("#FF2F66B7")

                                //    margin.bottomOffset: ui.sdu(5)
                                //    margin.leftOffset: ui.sdu(2)
                                // }
                                // Label {
                                
                                // }

                            }
                        }
                        ImageView {
                            id: subdLogo

                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center

                            preferredHeight: ui.sdu(17)
                            preferredWidth: ui.sdu(17)

                            imageSource: "asset:///images/img/household_icon_nfill.png"
                        }
                    }

                    Container {
                        margin.leftOffset: ui.sdu(6)

                        layout: StackLayout {
                            orientation: LayoutOrientation.TopToBottom
                        }
                        
                        Divider {
                        }

                        Container {
                            visible: true
                            margin.bottomOffset: ui.sdu(2)

                            ConnectLabel {
                                text: "Email Address"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                            }

                            ConnectTextField {
                                id: tfEmail
                                text: _control.m
                                hintText: "Email Address"
                                margin.rightOffset: ui.sdu(6)
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                            }

                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }

                        Container {
                            margin.bottomOffset: ui.sdu(2)

                            ConnectLabel {
                                text: "Locality"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                            }

                            ConnectLabel {
                                id: tfLocality
                                text: _control.myDetails.itemData.Locality.Name
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                                margin.bottomOffset: ui.sdu(2)
                                margin.rightOffset: ui.sdu(6)
                            }
                        }

                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }
                        
                        Container {
                            visible: true
                            margin.bottomOffset: ui.sdu(2)

                            ConnectLabel {
                                text: "Subdivision"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                            }

                            ConnectLabel {
                                id: tfSubdivision
                                text: _control.myDetails.itemData.Subdivision.Name
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                                margin.bottomOffset: ui.sdu(2)
                                margin.rightOffset: ui.sdu(6)

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }

                        Container {
                            margin.bottomOffset: ui.sdu(2)

                            ConnectLabel {
                                text: "Address"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                            }
                            ConnectTextField {
                                id: tfAddress
                                text: _control.myDetails.itemData.FormattedAddress
                                hintText: "Address"
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                                margin.rightOffset: ui.sdu(6)

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }

                        Container {
                            margin.bottomOffset: ui.sdu(2)

                            ConnectLabel {
                                text: "Home Phone"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                            }
                            ConnectTextField {
                                id: tfLandline
                                text: _control.myDetails.itemData.HomePhone
                                hintText: "Home Phone"
                                inputMode: TextFieldInputMode.PhoneNumber
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                                margin.rightOffset: ui.sdu(6)

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }

                        Container {
                            margin.bottomOffset: ui.sdu(2)

                            ConnectLabel {
                                text: "Work Phone"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                            }
                            ConnectTextField {
                                id: tfWorkNumber
                                text: _control.myDetails.itemData.WorkPhone
                                hintText: "Work Phone"
                                inputMode: TextFieldInputMode.PhoneNumber
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                                margin.rightOffset: ui.sdu(6)

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }

                        Container {
                            margin.bottomOffset: ui.sdu(2)

                            ConnectLabel {
                                text: "Mobile Phone"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                            }
                            ConnectTextField {
                                id: tfMobileNumber
                                text: _control.myDetails.itemData.MobilePhone
                                hintText: "Mobile Phone"
                                inputMode: TextFieldInputMode.PhoneNumber
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                                margin.rightOffset: ui.sdu(6)

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }

                        Container {
                            preferredWidth: maxWidth
                            margin.topOffset: ui.sdu(4)
                            layout: DockLayout {

                            }

                            Label {
                                text: "Family Updates"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                                horizontalAlignment: HorizontalAlignment.Left
                            }

                            CheckBox {
                                id: tfFamilyUpdates
                                margin.rightOffset: ui.sdu(3)
                                horizontalAlignment: HorizontalAlignment.Right
                                checked: _control.familyUpdates
                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }
                        
                        Container {
                            margin.topOffset: ui.sdu(4)
                            preferredWidth: maxWidth
                            layout: DockLayout {

                            }

                            Label {
                                text: "Photo Updates"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                                horizontalAlignment: HorizontalAlignment.Left
                            }

                            CheckBox {
                                id: tfPhotoUpdates
                                checked: _control.photoUpdates
                                margin.rightOffset: ui.sdu(3)
                                horizontalAlignment: HorizontalAlignment.Right

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }
                        
                        Container {
                            margin.topOffset: ui.sdu(4)
                            preferredWidth: maxWidth
                            layout: DockLayout {

                            }

                            Label {
                                text: "Display Work Phone"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                                horizontalAlignment: HorizontalAlignment.Left
                            }

                            CheckBox {
                                id: tfDisplayWorkPhone
                                checked: _control.displayWorkPhone
                                margin.rightOffset: ui.sdu(3)
                                horizontalAlignment: HorizontalAlignment.Right

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }
                        Container {
                            margin.topOffset: ui.sdu(4)
                            preferredWidth: maxWidth
                            layout: DockLayout {

                            }

                            Label {
                                text: "Display Mobile Phone"
                                textStyle.color: Color.create("#4c5a61")
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.Bold
                                horizontalAlignment: HorizontalAlignment.Left
                            }

                            CheckBox {
                                id: tfDisplayMobilePhone
                                checked: _control.displayMobilePhone
                                margin.rightOffset: ui.sdu(3)
                                horizontalAlignment: HorizontalAlignment.Right

                            }
                        }
                        
                        Divider {
                            margin.topOffset: ui.sdu(1.5)
                        }

                        Container {
                            preferredWidth: maxWidth
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            margin.topOffset: ui.sdu(3)

                            ConnectTextArea {
                                margin.topOffset: ui.sdu(1)
                                margin.leftOffset: ui.sdu(1)
                                margin.rightOffset: ui.sdu(6)
                                margin.bottomOffset: ui.sdu(3)
                                id: tfComments
                                text: _control.myDetails.itemData.Comments
                                hintText: "Type your comments here..."
                                textStyle.color: Color.create("#9daeb5")
                                textStyle.fontSize: FontSize.Small
                                preferredHeight: ui.sdu(40)
                                
                                onTextChanging: {
                                    _control.setComments(tfComments.text);
                                }
                            }

                        }

                        Container {
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            margin.bottomOffset: ui.sdu(10)
                            margin.rightOffset: ui.sdu(6)

                            margin.topOffset: ui.sdu(2)
                            
                            Container {
                                preferredWidth: maxWidth
                                preferredHeight: ui.sdu(12)
                                margin.rightOffset: ui.sdu(1)
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Bottom
                                layout: DockLayout {
                                }
                                
                                onTouch: {
                                    if (event.touchType == TouchType.Down) {
                                        //Do something on down touch - e.g. change background color
                                    } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                                        //Users finger has been lifted OR has left the element.
                                        onClicked: {
                                            _home.popScreen();
                                        }
                                    }
                                }
                                
                                ImageView {
                                    imageSource: "asset:///images/nineslice/rounded.amd"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    filterColor: Color.create("#d5dade")
                                }
                                ImageView {
                                    imageSource: "asset:///images/nineslice/rounded.amd"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    margin.bottomOffset: ui.sdu(0.3)
                                    margin.rightOffset: ui.sdu(0.3)
                                    margin.leftOffset: ui.sdu(0.3)
                                    margin.topOffset: ui.sdu(0.3)
                                    filterColor: Color.White
                                }
                                
                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Center
                                    
                                    textStyle.color: Color.create("#90a3ab")
                                    textStyle.fontSize: FontSize.XSmall
                                    textStyle.fontWeight: FontWeight.Bold
                                    text: "CANCEL"
                                
                                }
                            }

                            
                            Container {
                                preferredWidth: maxWidth
                                preferredHeight: ui.sdu(12)
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Bottom
                                layout: DockLayout {
                                }
                                
                                onTouch: {
                                    if (event.touchType == TouchType.Down) {
                                        //Do something on down touch - e.g. change background color
                                    } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                                        //Users finger has been lifted OR has left the element.
                                        onClicked: {
                                            loadingDialog.open();
                                            _control.changeRequestSent.connect(informUserAndClose)
                                            _control.sendChangeRequest();
                                        }
                                    }
                                }
                                
                                ImageView {
                                    imageSource: "asset:///images/nineslice/rounded.amd"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    filterColor: Color.create("#1978bb")
                                }
                                
                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Center
                                    
                                    textStyle.color: Color.White
                                    textStyle.fontSize: FontSize.XSmall
                                    textStyle.fontWeight: FontWeight.Bold
                                    text: "SUBMIT"
                                
                                }
                            }

                            attachedObjects: [
                                SystemToast {
                                    id: myQmlToast
                                    body: "The change request has been sent."
                                },

                                Dialog {
                                    id: loadingDialog

                                    Container {
                                        layout: DockLayout {

                                        }
                                        preferredWidth: maxWidth
                                        preferredHeight: displayInfo.resolution.height

                                        onCreationCompleted: {
                                            actvIndicator.start();
                                        }

                                        Container {
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill
                                            background: Color.create("#AA000000")

                                            layout: DockLayout {

                                            }

                                            Container {
                                                layout: StackLayout {
                                                    orientation: LayoutOrientation.LeftToRight

                                                }

                                                horizontalAlignment: HorizontalAlignment.Center
                                                verticalAlignment: VerticalAlignment.Center

                                                Container {
                                                    layoutProperties: StackLayoutProperties {
                                                        spaceQuota: 0.2
                                                    }

                                                }

                                                Container {
                                                    layoutProperties: StackLayoutProperties {
                                                        spaceQuota: 1
                                                    }
                                                    horizontalAlignment: HorizontalAlignment.Fill
                                                    verticalAlignment: VerticalAlignment.Fill

                                                    Container {
                                                        layout: DockLayout {

                                                        }

                                                        ImageView {
                                                            preferredWidth: maxWidth

                                                            imageSource: "asset:///images/nineslice/rounded.amd"
                                                            horizontalAlignment: HorizontalAlignment.Fill
                                                            verticalAlignment: VerticalAlignment.Fill
                                                            filterColor: Color.LightGray
                                                        }

                                                        Container {
                                                            horizontalAlignment: HorizontalAlignment.Fill
                                                            verticalAlignment: VerticalAlignment.Fill

                                                            layout: StackLayout {
                                                                orientation: LayoutOrientation.TopToBottom
                                                            }
                                                            ConnectLabel {
                                                                margin.topOffset: ui.sdu(3)
                                                                margin.leftOffset: ui.sdu(4)

                                                                text: "Sending change request."
                                                                textStyle.color: Color.Black
                                                                textStyle.fontSize: FontSize.Medium
                                                            }

                                                            Container {
                                                                layout: StackLayout {
                                                                    orientation: LayoutOrientation.LeftToRight
                                                                }
                                                                margin.topOffset: ui.sdu(3)
                                                                margin.bottomOffset: ui.sdu(3)
                                                                margin.leftOffset: ui.sdu(4)

                                                                ActivityIndicator {

                                                                    verticalAlignment: VerticalAlignment.Center
                                                                    id: actvIndicator
                                                                    enabled: true

                                                                    preferredHeight: ui.sdu(8)
                                                                    preferredWidth: ui.sdu(8)
                                                                }

                                                                ConnectLabel {
                                                                    margin.leftOffset: ui.sdu(2)
                                                                    verticalAlignment: VerticalAlignment.Center
                                                                    text: "Please wait..."
                                                                    textStyle.color: Color.DarkGray
                                                                    textStyle.fontSize: FontSize.Small

                                                                }
                                                            }

                                                        }

                                                    }

                                                }

                                                Container {
                                                    layoutProperties: StackLayoutProperties {
                                                        spaceQuota: 0.2
                                                    }

                                                }

                                            }
                                        }

                                        attachedObjects: [
                                            DisplayInfo {
                                                id: displayInfo
                                            }
                                        ]
                                    }

                                }
                            ]
                        }

                    }
                }
            }

            ActivityIndicator {
                id: contentLoadingIndicator
                objectName: "actLoadingIndicator"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                preferredWidth: 100
                margin.topOffset: 20
            }
        }
    }
}
