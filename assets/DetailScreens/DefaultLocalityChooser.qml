import bb.cascades 1.4
import my.library 1.0
import bb.platform 1.3
import bb.device 1.4
import "../custom"

Page {

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
                text: "Set default locality"
                textStyle.color: Color.White
                textStyle.fontSize: FontSize.Small
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center

            }
        }

        Container {

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
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }

                ActivityIndicator {
                    id: contentLoadingIndicator
                    objectName: "contentLoadingIndicator"
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: 100
                    margin.topOffset: 20
                }

                //Current Locality
                Container {
                    layout: DockLayout {

                    }
                    background: Color.create("#fafafa")
                    
                    leftPadding: ui.sdu(3)
                    topPadding: ui.sdu(5)
                    bottomPadding: ui.sdu(5)
                    rightPadding: ui.sdu(3)
                    
                    horizontalAlignment: HorizontalAlignment.Fill
                    preferredWidth: maxWidth

                    ConnectLabel {
                        
                        text: "Current Default:"
                        textStyle.color: Color.DarkGray
                        horizontalAlignment: HorizontalAlignment.Left
                        verticalAlignment: VerticalAlignment.Center
                    }
                    ConnectLabel {
                       
                        text: _control.currentLocalityName
                        textStyle.color: Color.create("#2d85c2")
                        horizontalAlignment: HorizontalAlignment.Right
                        verticalAlignment: VerticalAlignment.Center
                    }

                }


                ListView {
                    id: country_listview
                    objectName: "country_listview"

                    onTriggered: {
                        var selectedItem = dataModel.data(indexPath);

                        _control.openLocalityChooser(selectedItem.Code, selectedItem.Name);

                    }

                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            CustomListItem {
                                dividerVisible: true

                                Container {
                                    id: container
                                    preferredWidth: maxWidth
                                    margin.leftOffset: ui.sdu(3)
                                    margin.rightOffset: ui.sdu(3)
                                    verticalAlignment: VerticalAlignment.Center

                                    layout: DockLayout {
                                    }

                                    ConnectLabel {
                                        horizontalAlignment: HorizontalAlignment.Left
                                        verticalAlignment: VerticalAlignment.Center

                                        text: ListItemData.Name
                                        textStyle {
                                            base: SystemDefaults.TextStyles.BodyText
                                            color: Color.create("#485b64")
                                        }
                                    }
                                }
                            }
                        }
                    ]

                }
            }

        }
    }
}
