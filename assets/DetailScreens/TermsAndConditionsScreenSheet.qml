import bb.cascades 1.4
import "../custom"

Sheet {

    Page {

        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            onTouch: {
                _control.onTouchFunc();
            }
            Container {
                preferredHeight: ui.sdu(24)
                background: Color.create("#1978bb")
                horizontalAlignment: HorizontalAlignment.Fill
                layout: DockLayout {
                }
                
                ConnectLabel {
                    horizontalAlignment: HorizontalAlignment.Left
                    verticalAlignment: VerticalAlignment.Center
                    text: "Close"
                    margin.leftOffset: ui.sdu(3)
                    textStyle.color: Color.White
                    textStyle.fontSize: FontSize.XXSmall
                    textFormat: TextFormat.Html
                    gestureHandlers: [
                        TapHandler {
                            onTapped: {
                                close();
                            }
                        }
                    ]
                }

                ConnectLabel {
                    text: "Terms & Conditions"
                    textStyle.color: Color.White
                    textStyle.fontSize: FontSize.Small
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center

                }
            }

            Container {
                horizontalAlignment: HorizontalAlignment.Center

                layout: StackLayout {

                }
                layoutProperties: AbsoluteLayoutProperties {

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
                        visible: true
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
                    id: contentLoadingIndicator
                    objectName: "contentLoadingIndicator"
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                    preferredWidth: 100
                    margin.topOffset: 20
                }

                TextArea {
                    verticalAlignment: VerticalAlignment.Center
                    editable: false
                    visible: (typeof _control.m_termsnConditions.TermsAndConditions === 'undefined' ? false : true)
                    scrollMode: scrollMode.Elastic

                    text: "<html><span style='font-family:Helvetica,Arial,Sans-Serif;'>" + _control.m_termsnConditions.TermsAndConditions + "</span></html>"
                    hintText: ""
                    backgroundVisible: true
                    textStyle.textAlign: TextAlign.Default
                    horizontalAlignment: HorizontalAlignment.Left
                }
            }
        }
    }
}