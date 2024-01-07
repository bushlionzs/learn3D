

#include "elements/CEGUIDragContainer.h"
#include "CEGUIImageset.h"
#include <math.h>


namespace CEGUI
{
    
    
    const String DragContainer::WidgetTypeName("DragContainer");
    
    const String DragContainer::EventNamespace("DragContainer");
    const String DragContainer::EventDragStarted("DragStarted");
    const String DragContainer::EventDragEnded("DragEnded");
    const String DragContainer::EventDragPositionChanged("DragPositionChanged");
    const String DragContainer::EventDragEnabledChanged("DragEnabledChanged");
    const String DragContainer::EventDragAlphaChanged("DragAlphaChanged");
    const String DragContainer::EventDragMouseCursorChanged("DragMouseCursorChanged");
    const String DragContainer::EventDragThresholdChanged("DragThresholdChanged");
    const String DragContainer::EventDragDropTargetChanged("DragDropTargetChanged");
    
    DragContainerProperties::DragAlpha       DragContainer::d_dragAlphaProperty;
    DragContainerProperties::DragCursorImage DragContainer::d_dragCursorImageProperty;
    DragContainerProperties::DraggingEnabled DragContainer::d_dragEnabledProperty;
    DragContainerProperties::DragThreshold   DragContainer::d_dragThresholdProperty;

    

    DragContainer::DragContainer(const String& type, const String& name) :
        Window(type, name),
        d_draggingEnabled(true),
        d_leftMouseDown(false),
        d_dragging(false),
        d_dragThreshold(8.0f),
        d_dragAlpha(0.5f),
        d_dropTarget(0),
        d_dragCursorImage((const Image*)DefaultMouseCursor)
    {
        addDragContainerProperties();
    }

    DragContainer::~DragContainer(void)
    {
    }

    bool DragContainer::isDraggingEnabled(void) const
    {
        return d_draggingEnabled;
    }

    void DragContainer::setDraggingEnabled(bool setting)
    {
        if (d_draggingEnabled != setting)
        {
            d_draggingEnabled = setting;
            WindowEventArgs args(this);
            onDragEnabledChanged(args);
        }
    }

    bool DragContainer::isBeingDragged(void) const
    {
        return d_dragging;
    }

    float DragContainer::getPixelDragThreshold(void) const
    {
        return d_dragThreshold;
    }

    void DragContainer::setPixelDragThreshold(float pixels)
    {
        if (d_dragThreshold != pixels)
        {
            d_dragThreshold = pixels;
            WindowEventArgs args(this);
            onDragThresholdChanged(args);
        }
    }

    float DragContainer::getDragAlpha(void) const
    {
        return d_dragAlpha;
    }

    void DragContainer::setDragAlpha(float alpha)
    {
        if (d_dragAlpha != alpha)
        {
            d_dragAlpha = alpha;
            WindowEventArgs args(this);
            onDragAlphaChanged(args);
        }
    }

    const Image* DragContainer::getDragCursorImage(void) const
    {
        if (d_dragCursorImage == (const Image*)DefaultMouseCursor)
        {
            return System::getSingleton().getDefaultMouseCursor();
        }
        else
        {
            return d_dragCursorImage;
        }
    }

    void DragContainer::setDragCursorImage(const Image* image)
    {
        if (d_dragCursorImage != image)
        {
            d_dragCursorImage = image;
            WindowEventArgs args(this);
            onDragMouseCursorChanged(args);
        }
    }

    void DragContainer::setDragCursorImage(MouseCursorImage image)
    {
        setDragCursorImage((const Image*)image);
    }

    void DragContainer::setDragCursorImage(const String& imageset, const String& image)
    {
        setDragCursorImage(ImagesetManager::getSingleton().getImageset(imageset)->getImage(image));
    }

    Window* DragContainer::getCurrentDropTarget(void) const
    {
        return d_dropTarget;
    }

    void DragContainer::addDragContainerProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( DragContainer );
           CEGUI_ADD_STATICPROPERTY( &d_dragEnabledProperty );
           CEGUI_ADD_STATICPROPERTY( &d_dragAlphaProperty );
           CEGUI_ADD_STATICPROPERTY( &d_dragThresholdProperty );
           CEGUI_ADD_STATICPROPERTY( &d_dragCursorImageProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    bool DragContainer::isDraggingThresholdExceeded(const Point& local_mouse)
    {
        
        float	deltaX = fabsf(local_mouse.d_x - d_dragPoint.d_x);
        float	deltaY = fabsf(local_mouse.d_y - d_dragPoint.d_y);

        
        return (deltaX > d_dragThreshold || deltaY > d_dragThreshold) ? true : false;
    }

    void DragContainer::initialiseDragging(void)
    {
        
        if (d_draggingEnabled)
        {
            
            d_storedClipState = d_clippedByParent;
            setClippedByParent(false);
            d_storedAlpha = d_alpha;
            setAlpha(d_dragAlpha);
            d_startPosition = getPosition(Absolute);

            d_dragging = true;

            
            updateActiveMouseCursor();
        }
    }

    void DragContainer::doDragging(const Point& local_mouse)
    {
        setPosition(Absolute, getPosition(Absolute) + (local_mouse - d_dragPoint));

        WindowEventArgs args(this);
        onDragPositionChanged(args);
    }

    void DragContainer::updateActiveMouseCursor(void) const
    {
        MouseCursor::getSingleton().setImage(d_dragging ? getDragCursorImage() : getMouseCursor());
    }

    void DragContainer::drawSelf(float z)
    {
        
    }

    void DragContainer::onMouseButtonDown(MouseEventArgs& e)
    {
        Window::onMouseButtonDown(e);

        if (e.button == LeftButton)
        {
            
            if (captureInput())
            {
                
                Point localPos = (getMetricsMode() == Relative) ? 
                    relativeToAbsolute(screenToWindow(e.position)) :
                    screenToWindow(e.position);

                
                d_dragPoint = localPos;
                d_leftMouseDown = true;
            }

            e.handled = true;
        }

    }

    void DragContainer::onMouseButtonUp(MouseEventArgs& e)
    {
        Window::onMouseButtonUp(e);

        if (e.button == LeftButton)
        {
            if (d_dragging)
            {
                
                WindowEventArgs args(this);
                onDragEnded(args);
            }

            
            releaseInput();
            e.handled = true;
        }
    }

    void DragContainer::onMouseMove(MouseEventArgs& e)
    {
        Window::onMouseMove(e);

        
        Point localMousePos = (getMetricsMode() == Relative) ? 
            relativeToAbsolute(screenToWindow(e.position)) :
            screenToWindow(e.position);

        
        if (d_dragging)
        {
            doDragging(localMousePos);
       }
        
        else
        {
            
            if (d_leftMouseDown)
            {
                if (isDraggingThresholdExceeded(localMousePos))
                {
                    
                    WindowEventArgs args(this);
                    onDragStarted(args);
                }
            }
        }
    }

    void DragContainer::onCaptureLost(WindowEventArgs& e)
    {
        Window::onCaptureLost(e);

        
        if (d_dragging)
        {
            
            d_dragging = false;
            setPosition(Absolute, d_startPosition);
            setClippedByParent(d_storedClipState);
            setAlpha(d_storedAlpha);

            
            updateActiveMouseCursor();
        }

        d_leftMouseDown = false;
        d_dropTarget = 0;

        e.handled = true;
    }

    void DragContainer::onAlphaChanged(WindowEventArgs& e)
    {
        
        if (d_dragging)
        {
            d_storedAlpha = d_alpha;
            d_alpha = d_dragAlpha;
        }

        Window::onAlphaChanged(e);
    }

    void DragContainer::onClippingChanged(WindowEventArgs& e)
    {
        
        if (d_dragging)
        {
            d_storedClipState = d_clippedByParent;
            d_clippedByParent = false;
        }

        Window::onClippingChanged(e);
    }

    void DragContainer::onDragStarted(WindowEventArgs& e)
    {
        initialiseDragging();

        fireEvent(EventDragStarted, e, EventNamespace);
    }

    void DragContainer::onDragEnded(WindowEventArgs& e)
    {
        fireEvent(EventDragEnded, e, EventNamespace);

        
        if (d_dropTarget)
        {
            
            d_dropTarget->notifyDragDropItemDropped(this);
        }
    }

    void DragContainer::onDragPositionChanged(WindowEventArgs& e)
    {
        fireEvent(EventDragPositionChanged, e, EventNamespace);

        Window* root;

        if (0 != (root = System::getSingleton().getGUISheet()))
        {
            
            
            
            bool wasEnabled = d_enabled;
            d_enabled = false;
            
            Window* eventWindow = root->getChildAtPosition(MouseCursor::getSingleton().getPosition());
            d_enabled = wasEnabled;

            
            if (!eventWindow)
            {
                eventWindow = root;
            }

            
            if (eventWindow != d_dropTarget)
            {
                DragDropEventArgs args(eventWindow);
                args.dragDropItem = this;
                onDragDropTargetChanged(args);
            }
        }
    }

    void DragContainer::onDragEnabledChanged(WindowEventArgs& e)
    {
        fireEvent(EventDragEnabledChanged, e, EventNamespace);

        
        if (!d_draggingEnabled && d_dragging)
        {
            releaseInput();
        }
    }

    void DragContainer::onDragAlphaChanged(WindowEventArgs& e)
    {
        fireEvent(EventDragAlphaChanged, e, EventNamespace);

        if (d_dragging)
        {
            d_alpha = d_storedAlpha;
            onAlphaChanged(e);
        }
    }

    void DragContainer::onDragMouseCursorChanged(WindowEventArgs& e)
    {
        fireEvent(EventDragMouseCursorChanged, e, EventNamespace);

        updateActiveMouseCursor();
    }

    void DragContainer::onDragThresholdChanged(WindowEventArgs& e)
    {
        fireEvent(EventDragThresholdChanged, e, EventNamespace);
    }

    void DragContainer::onDragDropTargetChanged(DragDropEventArgs& e)
    {
        fireEvent(EventDragDropTargetChanged, e, EventNamespace);

        
        if (d_dropTarget)
        {
            d_dropTarget->notifyDragDropItemLeaves(this);
        }

        
        d_dropTarget = e.window;

        
        d_dropTarget->notifyDragDropItemEnters(this);
    }

} 
