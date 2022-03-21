import bb.cascades 1.4
import "custom"

ListView {
    id: listViewCountries
    dataModel: _control.m_countriesModel

    scrollIndicatorMode: ScrollIndicatorMode.None

    function itemType(data, indexPath) {
        return (indexPath == 0 ? "main" : "item");
    }

    onTriggered: {
        var selectedItem = dataModel.data(indexPath);
        if (indexPath > 0)
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

        },

        ListItemComponent {
            id: mainit
            type: "main"

            Container {
                id: containerHomeTop

                onCreationCompleted: {
                    containerHomeTop.ListItem.view.loadFilterBt();
                }

                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }

                horizontalAlignment: HorizontalAlignment.Fill

                Container {
                    id: imageNFilterContainer

                    background: back.imagePaint

                    horizontalAlignment: HorizontalAlignment.Fill

                    minHeight: 750
                    preferredHeight: 750

                    Container {
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 0.7
                        }
                    }

                    gestureHandlers: [

                        TapHandler {
                            onTapped: {
                                containerHomeTop.ListItem.view.openSearch();
                            }
                        }
                    ]

                    Container {
                        id: filterCard

                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Fill

                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1
                        }

                        //                                    Container {
                        //                                        layout: DockLayout {
                        //
                        //                                        }
                        //                                        horizontalAlignment: HorizontalAlignment.Fill
                        //
                        //                                        margin.leftOffset: ui.sdu(2)
                        //                                        margin.rightOffset: ui.sdu(2)
                        //
                        //
                        //                                        ImageView {
                        //                                            imageSource: "asset:///images/nineslice/rounded.amd"
                        //                                            horizontalAlignment: HorizontalAlignment.Fill
                        //                                            verticalAlignment: VerticalAlignment.Fill
                        //                                            filterColor: Color.White}
                        //
                        //                                        Container {
                        //                                            layout: StackLayout {
                        //                                                orientation: LayoutOrientation.TopToBottom
                        //                                            }
                        //
                        //
                        //
                        //
                        //
                        //                                            Container {
                        //                                                layout: StackLayout {
                        //                                                    orientation: LayoutOrientation.LeftToRight
                        //                                                }
                        //
                        //                                                margin.topOffset: ui.sdu(4)
                        //                                                margin.bottomOffset: ui.sdu(6)
                        //                                                margin.leftOffset: ui.sdu(4)
                        //                                                margin.rightOffset: ui.sdu(4)
                        //
                        //
                        //                                                ImageView {
                        //                                                    imageSource: "asset:///images/titleicons/icon_search.png"
                        //                                                    verticalAlignment: VerticalAlignment.Center
                        //                                                }
                        //
                        //                                                ConnectLabel {
                        //                                                    verticalAlignment: VerticalAlignment.Center
                        //
                        //                                                    margin.leftOffset: ui.sdu(1)
                        //                                                    text: "Search people and places"
                        //
                        //                                                    textStyle.color: Color.Gray
                        //                                                    textStyle.fontSize: FontSize.Small
                        //
                        //
                        //                                                }
                        //
                        //                                                gestureHandlers: [
                        //
                        //                                                    TapHandler {
                        //                                                        onTapped: {
                        //                                                            containerHomeTop.ListItem.view.openSearch();
                        //                                                        }
                        //                                                    }
                        //                                                ]
                        //
                        //
                        //                                            }
                        //
                        //                                            Container {
                        //                                                id: searchFilter
                        //                                                layout: DockLayout {
                        //
                        //                                                }
                        //                                                horizontalAlignment: HorizontalAlignment.Fill
                        //                                                preferredWidth: maxWidth
                        //
                        //
                        //                                                margin.topOffset: ui.sdu(3)
                        //                                                margin.bottomOffset: ui.sdu(4)
                        //                                                margin.leftOffset: ui.sdu(4)
                        //                                                margin.rightOffset: ui.sdu(4)
                        //
                        //                                                ConnectLabel {
                        //                                                    horizontalAlignment: HorizontalAlignment.Left
                        //
                        //
                        //                                                    text: "Filter by country"
                        //                                                    textStyle.fontSize: FontSize.XSmall
                        //                                                    textStyle.color: Color.Gray
                        //                                                }
                        //
                        //                                                Container {
                        //                                                    horizontalAlignment: HorizontalAlignment.Right
                        //
                        //                                                    layout: StackLayout {
                        //                                                        orientation: LayoutOrientation.LeftToRight
                        //                                                    }
                        //
                        //                                                    ConnectLabel {
                        //
                        //                                                        id: btCountryFilter
                        //                                                        objectName: "btCountryFilter"
                        //                                                        verticalAlignment: VerticalAlignment.Center
                        //
                        //                                                        text: "All Countries"
                        //                                                        textStyle.color: Color.Gray
                        //                                                        textStyle.fontSize: FontSize.Small
                        //
                        //                                                    }
                        //
                        //                                                    ImageView {
                        //                                                        imageSource: "asset:///images/tabicons/arrow_right.png"
                        //
                        //                                                        preferredHeight: ui.sdu(2)
                        //                                                        preferredWidth: ui.sdu(3)
                        //                                                        margin.topOffset: ui.sdu(0.2)
                        //
                        //                                                        verticalAlignment: VerticalAlignment.Center
                        //                                                    }
                        //
                        //
                        //                                                    gestureHandlers: [
                        //
                        //                                                        TapHandler {
                        //                                                            onTapped: {
                        //                                                                containerHomeTop.ListItem.view.selectCountryFilter();
                        //                                                            }
                        //                                                        }
                        //                                                    ]
                        //                                                }
                        //
                        //
                        //                                            }
                        //                                        }
                        //                                    }

                    }
                    attachedObjects: [
                        ImagePaintDefinition {
                            id: back
                            repeatPattern: RepeatPattern.XY
                            imageSource: "asset:///images/img/top_home_screen_2.jpg"
                        }
                    ]
                }

                Container {

                    layout: StackLayout {
                        orientation: LayoutOrientation.TopToBottom
                    }

                    margin.topOffset: ui.sdu(3)

                    Container {
                        preferredWidth: maxWidth
                        margin.leftOffset: ui.sdu(3)
                        margin.rightOffset: ui.sdu(3)
                        layout: DockLayout {

                        }

                        ConnectLabel {
                            horizontalAlignment: HorizontalAlignment.Left

                            verticalAlignment: VerticalAlignment.Center
                            text: "My default locality"
                            textStyle.color: Color.Gray
                            textStyle.fontSize: FontSize.Small
                        }

                        ImageView {
                            horizontalAlignment: HorizontalAlignment.Right

                            verticalAlignment: VerticalAlignment.Center
                            imageSource: "asset:///images/img/more_options_icons.png"

                            preferredHeight: ui.sdu(0.6)
                            preferredWidth: ui.sdu(3)

                            gestureHandlers: [

                                TapHandler {
                                    onTapped: {
                                        menuDialog.open();

                                    }
                                }
                            ]

                        }

                        attachedObjects: [
                            Dialog {
                                id: menuDialog
                                Container {

                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    preferredHeight: maxHeight
                                    preferredWidth: maxWidth

                                    background: Color.create("#80000000")

                                    layout: DockLayout {
                                    }

                                    Container {
                                        margin.topOffset: ui.sdu(25)

                                        background: Color.create("#D3D3D3")
                                        horizontalAlignment: HorizontalAlignment.Fill
                                        verticalAlignment: VerticalAlignment.Center
                                        preferredWidth: maxWidth

                                        // Set the size of the dialog relative to
                                        // the size of the screen that the app
                                        // is running on.

                                        layout: DockLayout {
                                        }

                                        Container {

                                            ImageView {
                                                imageSource: "asset:///images/nineslice/rounded.amd"
                                                horizontalAlignment: HorizontalAlignment.Fill
                                                verticalAlignment: VerticalAlignment.Fill
                                                filterColor: Color.create("#2d85c2")
                                            }
                                            //background: Color.create("#2d85c2")

                                            margin.bottomOffset: ui.sdu(4)
                                            margin.topOffset: ui.sdu(4)
                                            margin.leftOffset: ui.sdu(4)
                                            margin.rightOffset: ui.sdu(4)
                                            preferredWidth: maxWidth
                                            preferredHeight: ui.du(10)

                                            layout: DockLayout {

                                            }

                                            ConnectLabel {
                                                horizontalAlignment: HorizontalAlignment.Center
                                                verticalAlignment: VerticalAlignment.Center
                                                text: "Change default locality"
                                                textStyle.color: Color.White
                                            }

                                            gestureHandlers: [
                                                TapHandler {
                                                    onTapped: {
                                                        menuDialog.close();
                                                        containerHomeTop.ListItem.view.changeDefaultLocality();
                                                    }
                                                }
                                            ]

                                        }
                                    }

                                    gestureHandlers: [
                                        TapHandler {
                                            onTapped: {
                                                menuDialog.close();

                                            }
                                        }
                                    ]
                                }
                            }
                        ]
                    }

                    Container {
                        id: containerDefaultLocationBt

                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }

                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Center

                        margin.leftOffset: ui.sdu(3)
                        margin.rightOffset: ui.sdu(3)
                        margin.bottomOffset: ui.sdu(8)
                        margin.topOffset: ui.sdu(4)

                        Container {

                            layoutProperties: StackLayoutProperties {
                                spaceQuota: 1
                            }

                            layout: GridLayout {
                                columnCount: 1
                            }

                            horizontalAlignment: HorizontalAlignment.Fill
                            verticalAlignment: VerticalAlignment.Top

                            Container {
                                layout: DockLayout {

                                }

                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Top
                                margin.bottomOffset: ui.sdu(2)

                                ImageView {

                                    preferredHeight: ui.sdu(12)
                                    preferredWidth: ui.sdu(12)

                                    imageSource: "asset:///images/buttonimages/ellipse.png"
                                    filterColor: Color.create("#ffFF1744")
                                }

                                Label {

                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Center

                                    text: ListItemData.DefaultLocality.Name[0]
                                    textStyle.color: Color.White
                                    textStyle.fontWeight: FontWeight.W500
                                    textStyle.fontSize: FontSize.Large

                                }

                            }

                            ConnectLabel {

                                id: localityNameBt
                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Top

                                text: "Browse " + ListItemData.DefaultLocality.Name
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.W400
                                textStyle.color: Color.Black
                            }

                            ConnectLabel {
                                id: localitySubQt
                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Top

                                text: ListItemData.DefaultLocality.SubdivisionsCount + " subdivisions"
                                textStyle.fontSize: FontSize.Small
                                textStyle.color: Color.Gray
                            }

                            gestureHandlers: [

                                TapHandler {
                                    onTapped: {
                                        containerHomeTop.ListItem.view.localityBrowse();

                                    }
                                }
                            ]

                        }

                        Container { //vertical line
                            minHeight: 0
                            maxHeight: Infinity
                            preferredHeight: 0
                            verticalAlignment: VerticalAlignment.Fill
                            margin.topOffset: ui.sdu(6)
                            margin.bottomOffset: ui.sdu(2)

                            minWidth: 2
                            maxWidth: 2
                            preferredWidth: 2
                            horizontalAlignment: HorizontalAlignment.Right

                            background: Color.LightGray

                        }

                        Container {
                            layoutProperties: StackLayoutProperties {
                                spaceQuota: 1
                            }

                            layout: GridLayout {
                                columnCount: 1
                            }

                            horizontalAlignment: HorizontalAlignment.Fill
                            verticalAlignment: VerticalAlignment.Center

                            Container {
                                layout: DockLayout {

                                }

                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Top
                                margin.bottomOffset: ui.sdu(2)

                                ImageView {
                                    preferredHeight: ui.sdu(12)
                                    preferredWidth: ui.sdu(12)

                                    horizontalAlignment: HorizontalAlignment.Center
                                    imageSource: "asset:///images/buttonimages/ellipse.png"
                                    filterColor: Color.create("#ff0EBAB4")
                                }

                                Label {

                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Center

                                    text: ListItemData.DefaultCountry.Code
                                    textStyle.color: Color.White
                                    textStyle.fontWeight: FontWeight.W500
                                    textStyle.fontSize: FontSize.Large

                                }

                            }
                            ConnectLabel {
                                id: countryName
                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Top

                                textStyle.color: Color.Black
                                textStyle.fontSize: FontSize.Small
                                textStyle.fontWeight: FontWeight.W400
                                text: ListItemData.DefaultCountry.Name
                            }

                            ConnectLabel {
                                id: countryLocCount
                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Top

                                textStyle.color: Color.Gray
                                textStyle.fontSize: FontSize.Small
                                text: ListItemData.DefaultCountry.LocalitiesCount + (ListItemData.DefaultCountry.LocalitiesCount == 1 ? " locality" : " localities")
                            }

                            gestureHandlers: [

                                TapHandler {
                                    onTapped: {

                                        containerHomeTop.ListItem.view.countryBrowse();

                                    }
                                }
                            ]

                        }

                    }

                    Divider {
                    }

                    ConnectLabel {
                        margin.leftOffset: ui.sdu(3)
                        margin.rightOffset: ui.sdu(3)
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.bottomOffset: ui.sdu(3)
                        margin.topOffset: ui.sdu(2)

                        text: "Browse by country"
                        textStyle.color: Color.Gray
                        textStyle.fontSize: FontSize.Small
                    }

                    Divider {
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

    //                function loadFilterBt() {
    //                    _control.loadFilterBt();
    //                }

    function openSearch() {
        _control.openAction("searchAction");
    }

    function changeDefaultLocality() {
        _control.openAction("locationAction");
    }

}
