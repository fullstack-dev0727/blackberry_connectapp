import bb.cascades 1.4
import "DetailScreens"
import "custom"
import bb.device 1.4
import bb.system 1.2

TabbedPane {
    showTabsOnActionBar: false
    
    function hasAccessToCountry(country) {
        var i = 0;
        for (i = 0; i < _control.m_countriesModel.size(); i++) {
            
            var co = _control.m_countriesModel.data([i]);
            if (co.Code === country) {
                return true;
            }
        }
        return false;
    }
    
    function isGlobalSubs() {    
        
        return _control.m_countriesModel.size() > 2; 
    
    }    
    function loadMain() {    
        
        //_control.loadHomeContent();   
        //_control.checkSync();
        pinDialog1.open();
        
    }
    
    function openWalkT() {
        walkthroughScreen.open();    
    }

    function loadingDialog() {
        loadingDialog.open(); 
    }

    function logged() {
        loadingDialog.open(); 
        loadMain();
    }
    
    function loginFinished() {    
        
        loadingDialog.close();  
    }
    
    function popScreen() {    
        
        _control.popScreen();   
    
    }    
    
    function enterPin() {
        pinDialog1.open();
        _control.m_pincode = "";
        pinDialog1.showPinNumber();
    }
    
    function logout() {
        //erase tokens
        _control.eraseTokens();
        
        openLogin();
    }
    
    function openLogin()
    {
        //pop all the screens on navPane?
        loginScreen.open();
        
        //_control.popAll();
    }
    
    function openSync()
    {
        //pop all the screens on navPane?
        syncScreen.open();
    
    }
    
    onCreationCompleted: {
        _control.openWalkT.connect(openWalkT);
        _control.logged.connect(logged);
        _control.requestlogin.connect(openLogin);
        _control.finished.connect(loginFinished);
        _control.loading.connect(loadingDialog);
        _control.enterPin.connect(enterPin);
        //Verify if logged
        _control.verifyLogged();
    }
    
    
    Tab { 
        title: qsTr("Home") + Retranslate.onLocaleOrLanguageChanged
        imageSource: "asset:///images/tabicons/icon_home.png"
        backgroundColor: Color.Blue;
        
        delegateActivationPolicy: TabDelegateActivationPolicy.ActivateImmediately
        
        delegate: Delegate {
            id: searchPageDelegate
            
            NavigationPane {
                id: homeNavigation
                objectName: "homeNavigation"
                
                
                Page {
                    id: searchPage
                    
                    actions: [
                        ActionItem {
                            id: homeAction
                            objectName: "homeAction"
                            title: "Home"
                            imageSource: "asset:///images/menuicons/icon_home.png" 
                            ActionBar.placement: ActionBarPlacement.InOverflow
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
                                logout();
                            
                            
                            }
                        }
                    ]
                    
                    //---------------
                    //HOME CONTENT
                    //---------------
                    
                    Container {
                        id: homeContent
                        onTouch: {
                            _control.onTouchFunc();
                        }
                        function loadHomeContent()
                        {
                            
                            
                            // Load the content depending on the subs type
                            if (homeContent.count() == 0)
                                homeContent.add((_control.m_countriesModel.size() > 2) ? globalSubsLayout.createObject() : countrySubsLayout.createObject());
                            else      
                                homeContent.replace(0, (_control.m_countriesModel.size() > 2) ? globalSubsLayout.createObject() : countrySubsLayout.createObject());
                            
                            
                            loadingDialog.close();  
                            loginScreen.close();    
                        
                        }
                        
                        onCreationCompleted: {
                            _control.currentUserChanged.connect(loadHomeContent)
                        }                                
                        
                        
                        attachedObjects: [    
                            ComponentDefinition {
                                id: globalSubsLayout
                                source: "HomeContentGlobalFragment.qml"
                            
                            
                            },
                            ComponentDefinition {
                                id: countrySubsLayout
                                source: "HomeContentCountryFragment.qml"                                    
                            }                     
                        ]
                    
                    }
                
                
                }
                
                attachedObjects: [
                    ComponentDefinition {
                        id: searchScreen
                        source: "DetailScreens/SearchScreen.qml"
                    },
                    ComponentDefinition {
                        id: termsnConditionsScreen
                        source: "DetailScreens/TermsAndConditionsScreen.qml"
                    
                    },
                    ComponentDefinition {
                        id: contactScreen
                        source: "DetailScreens/ContactScreen.qml"
                    
                    },
                    ComponentDefinition {
                        id: countryScreen
                        source: "DetailScreens/CountryScreen.qml"
                    
                    },
                    ComponentDefinition {
                        id: householdScreen
                        source: "DetailScreens/HouseholdScreen.qml"
                    
                    } ,
                    ComponentDefinition {
                        id: subdivisionScreen
                        source: "DetailScreens/SubdivisionScreen.qml"
                    
                    },
                    ComponentDefinition {
                        id: localityScreen
                        source: "DetailScreens/LocalityScreen.qml"
                    
                    }                   
                
                ]
            
                //onPopTransitionEnded: { page.destroy(); }
            }
        
        }
    
    
    }
    
    attachedObjects: [
        LoginScreen {
            id: loginScreen
        },
        WalkthroughScreen {
            id: walkthroughScreen
        },
        Dialog {
            id: loadingDialog
            
            
            Container {
                layout: DockLayout {
                
                }
                preferredWidth: maxWidth
                preferredHeight: displayInfo.resolution.height;
                
                onCreationCompleted: {
                    actvIndicator.start();
                }
                
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill
                    background: Color.create("#AA000000");
                    
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
                                        
                                        text: "Logging in."
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
        
        
    }, Dialog {
             id: pinDialog1
             function showPinNumber(){
                 pin1.setImageSource((_control.getLength(_control.m_pincode) > 0) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
                 pin2.setImageSource((_control.getLength(_control.m_pincode) > 1) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
                 pin3.setImageSource((_control.getLength(_control.m_pincode) > 2) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
                 pin4.setImageSource((_control.getLength(_control.m_pincode) > 3) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
             }
             function addNumber(key) {
                 if (_control.getLength(_control.m_pincode) < 4) {
                     _control.setPinModel(_control.append(_control.m_pincode, key));
                     pinDialog1.showPinNumber();
                 }
                 
                 if (_control.getLength(_control.m_pincode) == 4) {
                     pinDialog1.clickedDone();
                 }
             }
             function deleteNumber() {
                 if (_control.getLength(_control.m_pincode) > 0) {
                     _control.setPinModel(_control.removeLast(_control.m_pincode));
                     pinDialog1.showPinNumber();
                 }
             }
             function clickedDone() {
                 if (_control.isExistedPinCode()) {
                     if (_control.checkPinCode(_control.m_pincode)) {
                         pinDialog1.close();
                         _control.checkSync();
                     } else {
                         pinCodeError2.show();
                         return;
                     } 
                 } else {
                     pinDialog1.close();
                     confirmPinDialog1.open();    
                 }
             }
             
             Container {

                 verticalAlignment: VerticalAlignment.Fill
                 horizontalAlignment: HorizontalAlignment.Fill
                 
                 layout: DockLayout {
                 
                 }
                background: Color.create("#ffffffff")
                Container {
                     horizontalAlignment: HorizontalAlignment.Center
                     ImageView {
                         imageSource: "asset:///images/img/pin_ic_header.png"
                         horizontalAlignment: HorizontalAlignment.Center
                         preferredWidth: 467.0
                         preferredHeight: 117.0
                         scalingMethod: ScalingMethod.AspectFill
                         margin.topOffset: 100.0
                     }
                     Label {
                         text: "Please enter your Pin\n"
                         horizontalAlignment: HorizontalAlignment.Center
                         textFit.maxFontSizeValue: 8.0
                         textStyle.color: Color.create("#ff646464")
                         margin.topOffset: 50.0
                     }
                     Container {
                         horizontalAlignment: HorizontalAlignment.Center
                         margin.topOffset: 20.0
                         layout: GridLayout {
                             columnCount: 4
                         }
                         ImageView {
                             id: pin1
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.leftOffset: 10.0
                             margin.rightOffset: 10.0
                         }
                         ImageView {
                             id: pin2
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.leftOffset: 10.0
                             margin.rightOffset: 10.0
                         }
                         ImageView {
                             id: pin3
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.rightOffset: 10.0
                             margin.leftOffset: 10.0
                         }
                         ImageView {
                             id: pin4
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.rightOffset: 10.0
                             margin.leftOffset: 10.0
                         }
                     }
                 }
                 Container {
                     
                     horizontalAlignment: HorizontalAlignment.Fill
                     verticalAlignment: VerticalAlignment.Bottom
                     Container {
                         layout: GridLayout {
                             columnCount: 3
                         
                         }
                         verticalAlignment: VerticalAlignment.Bottom
                         horizontalAlignment: HorizontalAlignment.Fill
                         background: Color.create("#fff0f0f0")
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                 
                            }
                             
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                             Label {
                                 text: "1"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("1");
                                 }
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                 
                             }
                             Label {
                                 text: "2"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("2");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                 
                             }
                             Label {
                                 text: "3"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("3");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                
                             }
                             Label {
                                 text: "4"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("4");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                 
                             }
                             Label {
                                 text: "5"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("5");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                
                             }
                             Label {
                                 text: "6" 
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("6");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                 
                             }
                             Label {
                                 text: "7"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("7");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                 
                             }
                             Label {
                                 text: "8"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("8");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                                 
                             }
                             Label {
                                 text: "9" 
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("9");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 scalingMethod: ScalingMethod.Fill
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             }
                             Label {
                                 text: "0"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         pinDialog1.addNumber("0");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 scalingMethod: ScalingMethod.AspectFit
                                 imageSource: "asset:///images/img/pin_delete.png"
                                onTouch: {
                                    if (event.touchType == TouchType.Up)
                                        pinDialog1.deleteNumber();
                                }

                            }
                             
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                     }
                 
                 }
             
             }
         },
         Dialog {
             id: confirmPinDialog1
             function showPinNumber(){
                 confirmPin1.setImageSource((_control.getLength(_control.m_pincode1) > 0) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
                 confirmPin2.setImageSource((_control.getLength(_control.m_pincode1) > 1) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
                 confirmPin3.setImageSource((_control.getLength(_control.m_pincode1) > 2) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
                 confirmPin4.setImageSource((_control.getLength(_control.m_pincode1) > 3) ? "asset:///images/img/pin_selected.png" : "asset:///images/img/pin_deselected.png");
             }
             function addNumber(key) {
                 if (_control.getLength(_control.m_pincode1) < 4) {
                     _control.setPinModel1(_control.append(_control.m_pincode1, key));
                     confirmPinDialog1.showPinNumber();
                 }
                 
                 if (_control.getLength(_control.m_pincode1) == 4) {
                     confirmPinDialog1.clickedDone();
                 }
             }
             function deleteNumber() {
                 if (_control.getLength(_control.m_pincode1) > 0) {
                     _control.setPinModel1(_control.removeLast(_control.m_pincode1));
                     confirmPinDialog1.showPinNumber();
                 }
             }
             function clickedDone() {
                 if (_control.m_pincode == _control.m_pincode1) {
                     _control.setPinCode(_control.m_pincode);
                     confirmPinDialog1.close();
                     _control.checkSync();    
                 } else {
                     pinCodeError3.show();
                 }
             }
             
             Container {
                 
                 verticalAlignment: VerticalAlignment.Fill
                 horizontalAlignment: HorizontalAlignment.Fill
                 
                 layout: DockLayout {
                 
                 }
                 background: Color.create("#ffffffff")
                 Container {
                     horizontalAlignment: HorizontalAlignment.Center
                     ImageView {
                         imageSource: "asset:///images/img/pin_ic_header.png"
                         horizontalAlignment: HorizontalAlignment.Center
                         preferredWidth: 467.0
                         preferredHeight: 117.0
                         scalingMethod: ScalingMethod.AspectFill
                         margin.topOffset: 100.0
                     }
                     Label {
                         text: "Please confirm your Pin\n"
                         horizontalAlignment: HorizontalAlignment.Center
                         textFit.maxFontSizeValue: 8.0
                         textStyle.color: Color.create("#ff646464")
                         margin.topOffset: 50.0
                     }
                     Container {
                         horizontalAlignment: HorizontalAlignment.Center
                         margin.topOffset: 20.0
                         layout: GridLayout {
                             columnCount: 4
                         }
                         ImageView {
                             id: confirmPin1
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.leftOffset: 10.0
                             margin.rightOffset: 10.0
                         }
                         ImageView {
                             id: confirmPin2
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.leftOffset: 10.0
                             margin.rightOffset: 10.0
                         }
                         ImageView {
                             id: confirmPin3
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.rightOffset: 10.0
                             margin.leftOffset: 10.0
                         }
                         ImageView {
                             id: confirmPin4
                             imageSource: "asset:///images/img/pin_deselected.png"
                             horizontalAlignment: HorizontalAlignment.Center
                             preferredWidth: 120.0
                             preferredHeight: 120.0
                             scalingMethod: ScalingMethod.AspectFill
                             margin.rightOffset: 10.0
                             margin.leftOffset: 10.0
                         }
                     }
                 }
                 Container {
                     
                     horizontalAlignment: HorizontalAlignment.Fill
                     verticalAlignment: VerticalAlignment.Bottom
                     Container {
                         layout: GridLayout {
                             columnCount: 3
                         
                         }
                         verticalAlignment: VerticalAlignment.Bottom
                         horizontalAlignment: HorizontalAlignment.Fill
                         background: Color.create("#fff0f0f0")
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                             Label {
                                 text: "1"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("1");
                                 }
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "2"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("2");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "3"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("3");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "4"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("4");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "5"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("5");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "6" 
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("6");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "7"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("7");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "8"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("8");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             
                             }
                             Label {
                                 text: "9" 
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("9");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 scalingMethod: ScalingMethod.Fill
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 imageSource: "asset:///images/img/key_normal.png"
                                 scalingMethod: ScalingMethod.Fill
                             }
                             Label {
                                 text: "0"
                                 textStyle.textAlign: TextAlign.Center
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 textFit.maxFontSizeValue: 12.0
                                 textFit.minFontSizeValue: 12.0
                                 textStyle.color: Color.create("#aa537984")
                                 margin.topOffset: 15.0
                                 margin.bottomOffset: 15.0
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.addNumber("0");
                                 }
                             }
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                         Container {
                             ImageView {
                                 horizontalAlignment: HorizontalAlignment.Fill
                                 verticalAlignment: VerticalAlignment.Fill
                                 scalingMethod: ScalingMethod.AspectFit
                                 imageSource: "asset:///images/img/pin_delete.png"
                                 onTouch: {
                                     if (event.touchType == TouchType.Up)
                                         confirmPinDialog1.deleteNumber();
                                 }
                             
                             }
                             
                             horizontalAlignment: HorizontalAlignment.Fill
                             verticalAlignment: VerticalAlignment.Fill
                             layout: DockLayout {
                             
                             }
                         }
                     }
                 
                 }
             
             }
         },
         SystemToast {
             id: pinCodeError1
             body: "Please enter 4 digits for Pin!"
         },
         SystemToast {
              id: pinCodeError2
              body: "Incorrect Pin!"
         },
         SystemToast {
             id: pinCodeError3
             body: "Mismatched Pin!"
         }
    ]        

}
