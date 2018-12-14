/*
  ==============================================================================

    blueprint_View.cpp
    Created: 26 Nov 2018 3:38:37am

  ==============================================================================
*/


namespace blueprint
{

    namespace
    {

        //==============================================================================
        std::map<juce::String, YGDirection> ValidDirectionValues {
            { YGDirectionToString(YGDirectionInherit), YGDirectionInherit },
            { YGDirectionToString(YGDirectionLTR), YGDirectionLTR },
            { YGDirectionToString(YGDirectionRTL), YGDirectionRTL },
        };

        std::map<juce::String, YGFlexDirection> ValidFlexDirectionValues {
            { YGFlexDirectionToString(YGFlexDirectionColumn), YGFlexDirectionColumn },
            { YGFlexDirectionToString(YGFlexDirectionColumnReverse), YGFlexDirectionColumnReverse },
            { YGFlexDirectionToString(YGFlexDirectionRow), YGFlexDirectionRow },
            { YGFlexDirectionToString(YGFlexDirectionRowReverse), YGFlexDirectionRowReverse },
        };

        std::map<juce::String, YGJustify> ValidJustifyValues {
            { YGJustifyToString(YGJustifyFlexStart), YGJustifyFlexStart },
            { YGJustifyToString(YGJustifyCenter), YGJustifyCenter },
            { YGJustifyToString(YGJustifyFlexEnd), YGJustifyFlexEnd },
            { YGJustifyToString(YGJustifySpaceBetween), YGJustifySpaceBetween },
            { YGJustifyToString(YGJustifySpaceAround), YGJustifySpaceAround },
        };

        std::map<juce::String, YGAlign> ValidAlignValues {
            { YGAlignToString(YGAlignAuto), YGAlignAuto },
            { YGAlignToString(YGAlignFlexStart), YGAlignFlexStart },
            { YGAlignToString(YGAlignCenter), YGAlignCenter },
            { YGAlignToString(YGAlignFlexEnd), YGAlignFlexEnd },
            { YGAlignToString(YGAlignStretch), YGAlignStretch },
            { YGAlignToString(YGAlignBaseline), YGAlignBaseline },
            { YGAlignToString(YGAlignSpaceBetween), YGAlignSpaceBetween },
            { YGAlignToString(YGAlignSpaceAround), YGAlignSpaceAround },
        };

        std::map<juce::String, YGPositionType> ValidPositionTypeValues {
            { YGPositionTypeToString(YGPositionTypeRelative), YGPositionTypeRelative },
            { YGPositionTypeToString(YGPositionTypeAbsolute), YGPositionTypeAbsolute },
        };

        std::map<juce::String, YGWrap> ValidFlexWrapValues {
            { YGWrapToString(YGWrapNoWrap), YGWrapNoWrap },
            { YGWrapToString(YGWrapWrap), YGWrapWrap },
            { YGWrapToString(YGWrapWrapReverse), YGWrapWrapReverse },
        };

        std::map<juce::String, YGOverflow> ValidOverflowValues {
            { YGOverflowToString(YGOverflowVisible), YGOverflowVisible },
            { YGOverflowToString(YGOverflowHidden), YGOverflowHidden },
            { YGOverflowToString(YGOverflowScroll), YGOverflowScroll },
        };

        std::map<juce::String, YGEdge> ValidEdgeValues {
            { YGEdgeToString(YGEdgeLeft), YGEdgeLeft },
            { YGEdgeToString(YGEdgeTop), YGEdgeTop },
            { YGEdgeToString(YGEdgeRight), YGEdgeRight },
            { YGEdgeToString(YGEdgeBottom), YGEdgeBottom },
            { YGEdgeToString(YGEdgeStart), YGEdgeStart },
            { YGEdgeToString(YGEdgeEnd), YGEdgeEnd },
            { YGEdgeToString(YGEdgeHorizontal), YGEdgeHorizontal },
            { YGEdgeToString(YGEdgeVertical), YGEdgeVertical },
            { YGEdgeToString(YGEdgeAll), YGEdgeAll },
        };

        //==============================================================================
        template<typename T>
        bool validateFlexProperty (juce::String value, std::map<juce::String, T> validValues)
        {
            for (const auto& [flexValue, enumValue] : validValues)
            {
                if (value.equalsIgnoreCase(flexValue))
                {
                    return true;
                }
            }

            return false;
        }

    }

    //==============================================================================
    void View::setProperty (const juce::Identifier& name, const juce::var& newValue)
    {
        // First, set the value on our own property map
        auto& props = getProperties();
        props.set(name, newValue);

        //==============================================================================
        // Flex enums
        if (name == juce::Identifier("direction"))
        {
            jassert (validateFlexProperty(newValue, ValidDirectionValues));
            YGNodeStyleSetDirection(yogaNode, ValidDirectionValues[newValue]);
        }

        if (name == juce::Identifier("flex-direction"))
        {
            jassert (validateFlexProperty(newValue, ValidFlexDirectionValues));
            YGNodeStyleSetFlexDirection(yogaNode, ValidFlexDirectionValues[newValue]);
        }

        if (name == juce::Identifier("justify-content"))
        {
            jassert (validateFlexProperty(newValue, ValidJustifyValues));
            YGNodeStyleSetJustifyContent(yogaNode, ValidJustifyValues[newValue]);
        }

        if (name == juce::Identifier("align-items"))
        {
            jassert (validateFlexProperty(newValue, ValidAlignValues));
            YGNodeStyleSetAlignItems(yogaNode, ValidAlignValues[newValue]);
        }

        if (name == juce::Identifier("align-content"))
        {
            jassert (validateFlexProperty(newValue, ValidAlignValues));
            YGNodeStyleSetAlignContent(yogaNode, ValidAlignValues[newValue]);
        }

        if (name == juce::Identifier("align-self"))
        {
            jassert (validateFlexProperty(newValue, ValidAlignValues));
            YGNodeStyleSetAlignSelf(yogaNode, ValidAlignValues[newValue]);
        }

        if (name == juce::Identifier("position"))
        {
            jassert (validateFlexProperty(newValue, ValidPositionTypeValues));
            YGNodeStyleSetPositionType(yogaNode, ValidPositionTypeValues[newValue]);
        }

        if (name == juce::Identifier("flex-wrap"))
        {
            jassert (validateFlexProperty(newValue, ValidFlexWrapValues));
            YGNodeStyleSetFlexWrap(yogaNode, ValidFlexWrapValues[newValue]);
        }

        if (name == juce::Identifier("overflow"))
        {
            jassert (validateFlexProperty(newValue, ValidOverflowValues));
            YGNodeStyleSetOverflow(yogaNode, ValidOverflowValues[newValue]);
        }

        //==============================================================================
        // Flex floats
        if (name == juce::Identifier("flex"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetFlex(yogaNode, newValue);
        }

        if (name == juce::Identifier("flex-grow"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetFlexGrow(yogaNode, newValue);
        }

        if (name == juce::Identifier("flex-shrink"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetFlexShrink(yogaNode, newValue);
        }

        if (name == juce::Identifier("flex-basis"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetFlexBasis(yogaNode, newValue);
        }

        if (name == juce::Identifier("width"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetWidth(yogaNode, newValue);
        }

        if (name == juce::Identifier("height"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetHeight(yogaNode, newValue);
        }

        if (name == juce::Identifier("min-width"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetMinWidth(yogaNode, newValue);
        }

        if (name == juce::Identifier("min-height"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetMinHeight(yogaNode, newValue);
        }

        if (name == juce::Identifier("max-width"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetMaxWidth(yogaNode, newValue);
        }

        if (name == juce::Identifier("max-height"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetMaxHeight(yogaNode, newValue);
        }

        if (name == juce::Identifier("aspect-ratio"))
        {
            jassert (newValue.isDouble());
            YGNodeStyleSetAspectRatio(yogaNode, newValue);
        }

        //==============================================================================
        // Flex position
        for (const auto& [edgeName, enumValue] : ValidEdgeValues)
        {
            if (name == juce::Identifier(edgeName))
            {
                YGNodeStyleSetPosition(yogaNode, enumValue, newValue);
                break;
            }
        }

        //==============================================================================
        // Margin & Padding
        juce::String prefix = name.toString().upToFirstOccurrenceOf("-", false, false);
        juce::String suffix = name.toString().fromLastOccurrenceOf("-", false, false);

        if (suffix.isEmpty() || prefix == suffix)
            suffix = "all";

        if (prefix == "margin")
        {
            for (const auto& [edgeName, enumValue] : ValidEdgeValues)
            {
                if (suffix == edgeName)
                {
                    YGNodeStyleSetMargin(yogaNode, enumValue, newValue);
                    break;
                }
            }
        }

        if (prefix == "padding")
        {
            for (const auto& [edgeName, enumValue] : ValidEdgeValues)
            {
                if (suffix == edgeName)
                {
                    YGNodeStyleSetPadding(yogaNode, enumValue, newValue);
                    break;
                }
            }
        }
    }

    void View::appendChild (View* childView)
    {
        // Add the child view to our component heirarchy and style tree.
        addAndMakeVisible(childView);
        YGNodeInsertChild(yogaNode, childView->yogaNode, YGNodeGetChildCount(yogaNode));

        // Now we need to layout our children again...
        auto bounds = getCachedFlexLayout();
        YGNodeCalculateLayout(yogaNode, bounds.getWidth(), bounds.getHeight(), YGDirectionInherit);

        // And then we need to actually draw the children again.
        resized();
    }

    //==============================================================================
    juce::Rectangle<float> View::getCachedFlexLayout()
    {
        return {
            YGNodeLayoutGetLeft(yogaNode),
            YGNodeLayoutGetTop(yogaNode),
            YGNodeLayoutGetWidth(yogaNode),
            YGNodeLayoutGetHeight(yogaNode)
        };
    }

    //==============================================================================
    void View::paint (juce::Graphics& g)
    {
        const auto& props = getProperties();

        if (props.contains("background-color"))
        {
                juce::Colour bgColour = juce::Colour::fromString(props["background-color"].toString());

            if (!bgColour.isTransparent())
                g.fillAll(bgColour);
        }
    }

    void View::resized()
    {
        const auto& props = getProperties();

        // Sanity check
        jassert (getNumChildComponents() == YGNodeGetChildCount(yogaNode));

        // Debugging support for Yoga's layout.
        if (props.contains("debug"))
            YGNodePrint(yogaNode, (YGPrintOptions) (YGPrintOptionsLayout
                                                    | YGPrintOptionsStyle
                                                    | YGPrintOptionsChildren));

        // Update our own bounds
        setBounds(getCachedFlexLayout().toNearestInt());

        // Then assign child bounds
        for (int i = 0; i < getNumChildComponents(); ++i)
            if (View* v = dynamic_cast<View*>(getChildComponent(i)))
                v->resized();
    }

}