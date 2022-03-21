import bb.cascades 1.4
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

            ConnectLabel {
                text: "Browse Other Countries"
                textStyle.color: Color.White
                textStyle.fontSize: FontSize.Small
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center

            }
        }

        ListView {
            id: listViewCountries
            dataModel: _control.m_countriesModel

            scrollIndicatorMode: ScrollIndicatorMode.None

            function itemType(data, indexPath) {
                return "item";
            }

            onTriggered: {
                var selectedItem = dataModel.data(indexPath);
                _control.openCountry(selectedItem.Code, selectedItem.Name);
            }

            listItemComponents: [
                ListItemComponent {
                    type: "item"

                    CustomListItem {
                        dividerVisible: true

                        Container {

                            margin.topOffset: ui.sdu(3)
                            margin.leftOffset: ui.sdu(3)
                            margin.rightOffset: ui.sdu(3)

                            layout: DockLayout {
                            }

                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                preferredWidth: maxWidth
                                layout: DockLayout {

                                }

                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Left
                                    verticalAlignment: VerticalAlignment.Center

                                    text: ListItemData.Name
                                    textStyle {
                                        base: SystemDefaults.TextStyles.BodyText
                                        color: Color.Black
                                    }
                                }

                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Right
                                    verticalAlignment: VerticalAlignment.Center

                                    text: ListItemData.LocalitiesCount + (ListItemData.LocalitiesCount == 1 ? " locality" : " localities")
                                    textStyle {
                                        base: SystemDefaults.TextStyles.PrimaryText
                                        fontSizeValue: 90
                                        color: Color.DarkGray
                                    }
                                }

                            }
                        }
                    }

                }
            ]

            function localityBrowse() {
                _control.openDefLocality();
            }
            function countryBrowse() {
                _control.openDefCountry();
            }

            function selectCountryFilter() {
                _control.selectCountryFilter();
            }

            function openSearch() {
                _control.openAction("searchAction");
            }

            function changeDefaultLocality() {
                _control.openAction("locationAction");
            }

        }
    }
}
