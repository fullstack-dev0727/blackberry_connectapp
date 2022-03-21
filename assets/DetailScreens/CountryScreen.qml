import bb.cascades 1.4
import my.library 1.0
import "../custom"

Page {

    actionBarAutoHideBehavior: ActionBarAutoHideBehavior.HideOnScroll
    actions: [
        ActionItem {
            id: homeAction
            objectName: "homeAction"
            title: "Home"
            imageSource: "asset:///images/titleicons/icon_home.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _control.openAction(homeAction.objectName);
            }
        },
        ActionItem {
            id: searchAction
            objectName: "searchAction"
            title: "Search"
            imageSource: "asset:///images/titleicons/icon_search.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _control.openAction(searchAction.objectName);
            }
        },
        ActionItem {
            id: detailsAction
            objectName: "detailsAction"
            title: "My Details"
            imageSource: "asset:///images/menuicons/my_details.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: {
                _control.openAction(detailsAction.objectName);
            }
        },
        ActionItem {
            id: locationAction
            objectName: "locationAction"
            title: "Default Locality"
            imageSource: "asset:///images/menuicons/my_default_locality.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: {
                _control.openAction(locationAction.objectName);
            }
        },
        ActionItem {
            id: termsAction
            objectName: "termsAction"
            title: "Term and conditions"
            imageSource: "asset:///images/menuicons/terms_n_conditions.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: {
                _control.openAction(termsAction.objectName);
            }
        },
        ActionItem {
            id: contactAction
            objectName: "contactAction"
            title: "Contact UBT"
            imageSource: "asset:///images/menuicons/contact_ubt.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: {
                _control.openAction(contactAction.objectName);
            }
        },
        ActionItem {
            id: syncAction
            objectName: "syncAction"
            title: "Sync Data"
            imageSource: "asset:///images/menuicons/security.png" 
            ActionBar.placement: ActionBarPlacement.InOverflow                                        
            onTriggered: {
                _control.openAction(syncAction.objectName);
            }                                        
        },
        ActionItem {
            id: feedbackAction
            objectName: "feedbackAction"
            title: "Feedback"
            imageSource: "asset:///images/menuicons/contact_ubt.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            onTriggered: {
                _control.openAction(feedbackAction.objectName);
            }
        },
        ActionItem {
            ActionBar.placement: ActionBarPlacement.InOverflow
            title: "Log out"
            imageSource: "asset:///images/menuicons/logout.png"
            onTriggered: {
                _home.logout();

            }
        }
    ]

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
            //ImageView { 0717
            //    imageSource: "asset:///images/titleicons/icon.png"
            //    verticalAlignment: VerticalAlignment.Center
            //    horizontalAlignment: HorizontalAlignment.Left
            //}

            ConnectLabel {
                text: "Country Information"
                textStyle.color: Color.White
                textStyle.fontSize: FontSize.Small
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center

            }
        }

        Container {
            layout: DockLayout {

            }

            Container {
                visible: _control.noPermission
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }

                ConnectLabel {
                    margin.topOffset: ui.sdu(10)
                    margin.leftOffset: ui.sdu(5)
                    margin.rightOffset: ui.sdu(5)
                    text: "Seems like you don't have access to all Regions. Upgrade your plan to search for members from all around the world"
                    textStyle.textAlign: TextAlign.Center
                    multiline: true
                    textStyle.color: Color.DarkGray

                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center

                }

                ImageView {
                    margin.topOffset: ui.sdu(10)
                    imageSource: "asset:///images/img/external_icon.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    filterColor: Color.create("#2d85c2")
                }
                ConnectLabel {
                    text: "Manage Subscription"
                    textStyle.color: Color.create("#2d85c2")
                    textStyle.fontSize: FontSize.Large
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center

                }

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

            ActivityIndicator {
                id: actLoadingIndicator
                objectName: "actLoadingIndicator"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                preferredWidth: 100
                margin.topOffset: 20
            }

            Container {
                visible: (typeof _control.m_countryModel.Name === 'undefined' ? false : true)

                margin.topOffset: ui.du(3)
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }

                ListView {
                    id: country_listview
                    objectName: "country_listview"
                    horizontalAlignment: HorizontalAlignment.Fill

                    property bool loaded: false

                    onTriggered: {
                        if (indexPath > 0) {
                            var selectedItem = dataModel.data(indexPath);
                            _control.openLocality(selectedItem.Id, selectedItem.Name);
                        } else if (indexPath[0] == (dataModel.childCount([]) - 1)) { // Last item selected
                            _model.addItemsAt(indexPath);
                        }
                    }

                    function itemType(data, indexPath) {
                        return (indexPath == 0 ? "main" : "item");
                    }

                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            CustomListItem {
                                dividerVisible: true
                                Container {

                                    horizontalAlignment: HorizontalAlignment.Fill
                                    margin.topOffset: ui.du(4)
                                    margin.bottomOffset: ui.du(4)

                                    layout: DockLayout {
                                    }

                                    Container {
                                        horizontalAlignment: HorizontalAlignment.Left
                                        margin.leftOffset: ui.du(3)
                                        margin.rightOffset: ui.du(3)

                                        ConnectLabel {
                                            horizontalAlignment: HorizontalAlignment.Left
                                            verticalAlignment: VerticalAlignment.Center

                                            text: ListItemData.Name
                                            textStyle {
                                                base: SystemDefaults.TextStyles.BodyText
                                                color: Color.DarkGray
                                            }
                                        }

                                    }
                                }
                            }
                        },
                        ListItemComponent {
                            type: "main"

                            Container {

                                horizontalAlignment: HorizontalAlignment.Fill

                                onCreationCompleted: {
                                    if (! mainItem.ListItem.view.loaded)
                                        mainItem.ListItem.view.loadLocalities(ListItemData.Code);
                                    mainItem.ListItem.view.loaded = true;
                                }

                                id: mainItem
                                layout: StackLayout {
                                    orientation: LayoutOrientation.TopToBottom
                                }

                                Container {
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    preferredWidth: maxWidth
                                    layout: DockLayout {

                                    }
                                    margin.bottomOffset: ui.du(3)
                                    margin.topOffset: ui.du(1)
                                    margin.leftOffset: ui.du(3)
                                    margin.rightOffset: ui.du(3)

                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.LeftToRight
                                        }

                                        horizontalAlignment: HorizontalAlignment.Left

                                        verticalAlignment: VerticalAlignment.Center

                                        Container {
                                            layout: DockLayout {

                                            }

                                            verticalAlignment: VerticalAlignment.Center
                                            horizontalAlignment: HorizontalAlignment.Center

                                            ImageView {
                                                preferredHeight: ui.sdu(11)
                                                preferredWidth: ui.sdu(11)

                                                horizontalAlignment: HorizontalAlignment.Center
                                                imageSource: "asset:///images/buttonimages/ellipse.png"
                                                filterColor: Color.create("#ff0EBAB4")
                                            }

                                            ConnectLabel {

                                                horizontalAlignment: HorizontalAlignment.Center
                                                verticalAlignment: VerticalAlignment.Center

                                                text: ListItemData.Code
                                                textStyle.color: Color.White
                                                textStyle.fontWeight: FontWeight.W500
                                                textStyle.fontSize: FontSize.Large

                                            }

                                        }

                                        ConnectLabel {
                                            text: ListItemData.Name
                                            margin.bottomOffset: ui.sdu(2)
                                            margin.leftOffset: ui.sdu(1.2)
                                            verticalAlignment: VerticalAlignment.Center
                                            textStyle {
                                                base: SystemDefaults.TextStyles.PrimaryText
                                                color: Color.create("#2d85c2")
                                                fontWeight: FontWeight.W500
                                            }

                                        }
                                    }

                                    Container {
                                        layout: StackLayout {
                                            orientation: LayoutOrientation.LeftToRight
                                        }

                                        horizontalAlignment: HorizontalAlignment.Right
                                        verticalAlignment: VerticalAlignment.Center

                                        ConnectLabel {
                                            verticalAlignment: VerticalAlignment.Center
                                            text: "Other Countries"

                                            textStyle {
                                                base: SystemDefaults.TextStyles.SubtitleText
                                                color: Color.create("#92a4ac")
                                            }

                                        }

                                        ImageView {
                                            verticalAlignment: VerticalAlignment.Center
                                            preferredHeight: ui.sdu(3)
                                            preferredWidth: ui.sdu(2)
                                            filterColor: Color.create("#92a4ac")
                                            imageSource: "asset:///images/tabicons//arrow_right.png"
                                        }
                                        gestureHandlers: [
                                            TapHandler {
                                                onTapped: {
                                                    mainItem.ListItem.view.browseOtherCountries();
                                                }
                                            }
                                        ]

                                    }
                                }

                                Divider {
                                }

                                Container {
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    margin.leftOffset: ui.du(3)
                                    margin.bottomOffset: ui.du(3)

                                    ImageView {
                                        verticalAlignment: VerticalAlignment.Center
                                        preferredHeight: ui.sdu(4)
                                        preferredWidth: ui.sdu(3)
                                        filterColor: Color.create("#2d85c2")
                                        imageSource: "asset:///images/titleicons/locality_icon.png"
                                    }

                                    ConnectLabel {
                                        text: ListItemData.LocalitiesCount + (ListItemData.LocalitiesCount == 1 ? " Locality" : " Localities")

                                        textStyle {
                                            base: SystemDefaults.TextStyles.PrimaryText
                                            color: Color.create("#2d85c2")
                                            fontWeight: FontWeight.W500
                                        }

                                    }
                                }

                                Divider {
                                }
                                ActivityIndicator {
                                    id: contentLoadingIndicator
                                    objectName: "contentLoadingIndicator"
                                    verticalAlignment: VerticalAlignment.Center
                                    horizontalAlignment: HorizontalAlignment.Center
                                    preferredWidth: 100
                                    margin.topOffset: 20
                                }

                            }

                        }
                    ]

                    function loadLocalities(code) {
                        _control.requestLocalities(code, 1);
                    }
                    
                    function browseOtherCountries() {
                        _control.browseOtherCountries();
                    }
                }
            }

        }
    }
}
