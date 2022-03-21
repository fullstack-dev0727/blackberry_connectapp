import bb.cascades 1.4
import my.library 1.0
import "../custom"

Page {
    
    
    
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }    
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        onTouch: {
            _control.onTouchFunc();
        }
        Container { 
            
            background: Color.create("#2d85c2") //blue
            layout: StackLayout { orientation: LayoutOrientation.TopToBottom} 
            topPadding: 20.0 
            bottomPadding: 20.0
            horizontalAlignment: HorizontalAlignment.Fill
            
            ConnectLabel { 
                visible: (typeof _control.m_localityModel.Name === 'undefined' ? false: true)
                text: _control.allDone ? "Sync Completed!" :"Syncing data"
                textStyle.color: Color.White
                horizontalAlignment: HorizontalAlignment.Center
            
            } 
            
            ConnectLabel {
                visible: (typeof _control.m_localityModel.Name === 'undefined' ? false: true)
                id: labelInfo 
                text: "Please, do not close the app."
                textStyle.color: Color.White 
                textStyle.fontSize: FontSize.Small
                horizontalAlignment: HorizontalAlignment.Center
            
            }
        } 
        
        Container {
            
            
            onCreationCompleted: {
                _control.invoke();
            }
            
            
            ScrollView {
                
                Container {
                    verticalAlignment: VerticalAlignment.Fill
                    horizontalAlignment: HorizontalAlignment.Fill
                    margin.leftOffset: ui.sdu(5)
                    margin.rightOffset: ui.sdu(5)
                    
                    layout: StackLayout {
                        orientation: LayoutOrientation.TopToBottom
                    }
                    
                    
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(10)
                        margin.rightOffset: ui.sdu(7)
                        margin.leftOffset: ui.sdu(7)
                        text:  "Please wait. Syncing data with server for offline access."
                        multiline: true
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: Color.DarkGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center
                    
                    } 
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(5)
                        margin.bottomOffset: ui.sdu(20)
                        text:  "Sync completed!"
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: Color.Blue 
                        visible: _control.allDone
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    } 
                    
                    Button {
                        id: btAction
                        text:  _control.allDone ? "Tap to close" : "Cancel" 
                        topMargin: ui.sdu(8)
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                        
                        onClicked: {
                            _control.allDone ? _control.close() : _control.cancel() 
                        }
                    }
                    
                    ProgressIndicator {
                        topMargin: ui.sdu(15)
                        id: progressIndicator
                        preferredWidth: maxWidth
                        preferredHeight: ui.sdu(20)
                        fromValue: 0
                        toValue: (_control.synctotal ? _control.synctotal : 0)              
                        value: (_control.syncprogress ? _control.syncprogress : 0) 
                    
                    }
                    
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(15)
                        text:  _control.creatingDone ? "Creating database... Done" : "Creating database..."
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.creatingDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    } 
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(2)
                        text:  _control.householdDone ? "Syncing households... Done" : "Syncing households..."
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.householdDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    }
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(2)
                        text:  _control.localityDone ? "Syncing localities... Done" : "Syncing localities..."
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.localityDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    } 
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(2)
                        text:  _control.subdivisionDone ? "Syncing subdivisions... Done" : "Syncing subdivisions..."
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.subdivisionDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    } 
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(2)
                        text:  _control.interchangeDone ? "Syncing interchanges... Done" : "Syncing interchanges..."
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.interchangeDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    } 
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(2)
                        text:  _control.countryDone ? "Syncing countries... Done" : "Syncing countries..." 
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.countryDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    } 
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(2)
                        text:  _control.photoDone ? "Syncing photos... Done" : "Syncing photos..." 
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.photoDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                    
                    } 
                    
                    ConnectLabel { 
                        margin.topOffset: ui.sdu(2)
                        text:  _control.photoExtDone ? "Extracting photos... Done" : "Extracting photos..." 
                        textStyle.textAlign: TextAlign.Center
                        textStyle.color: _control.countryDone ? Color.Dark : Color.LightGray 
                        
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Left
                        margin.leftOffset: ui.sdu(7)
                        margin.bottomOffset: ui.sdu(20)
                    
                    } 
                
                
                }
            
            }
        
        }
    }

}