/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CPROTECTEDCNODE_H__
#define __CPROTECTEDCNODE_H__


#include "2d/CCNode.h"

NS_CC_BEGIN
	
/**
 * @addtogroup _2d
 * @{
 */

/**
Node扩展，_protectedChildren主要是受保护节点数组添加
 *@brief A inner node type mainly used for UI module.
 * It is useful for composing complex node type and it's children are protected.
 */
class  CC_DLL ProtectedNode : public Node
{
public:
    /**
	二段构建函数
     * Creates a ProtectedNode with no argument.
     *@return A instance of ProtectedNode.
     */
    static ProtectedNode * create(void);
    
    /// @{
    /// @name Children and Parent
    
    /**
	添加受保护节点
     * Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child A child node
     */
    virtual void addProtectedChild(Node * child);
    /**
     * Adds a child to the container with a local z-order.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param localZOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     */
    virtual void addProtectedChild(Node * child, int localZOrder);
    /**
     * Adds a child to the container with z order and tag.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param localZOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @param tag       An integer to identify the node easily. Please refer to `setTag(int)`
     */
    virtual void addProtectedChild(Node* child, int localZOrder, int tag);
    /**
	根据tag获取受保护节点
     * Gets a child from the container with its tag.
     *
     * @param tag   An identifier to find the child node.
     *
     * @return a Node object whose tag equals to the input parameter.
     */
    virtual Node * getProtectedChildByTag(int tag);
    
    ////// REMOVES //////
    
    /**
	删除受保护节点以及是否调用cleanup()
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @param child     The child node which will be removed.
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeProtectedChild(Node* child, bool cleanup = true);
    
    /**
     * Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @param tag       An integer number that identifies a child node.
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeProtectedChildByTag(int tag, bool cleanup = true);
    
    /**
	删除所有受保护节点
     * Removes all children from the container with a cleanup.
     *
     * @see `removeAllChildrenWithCleanup(bool)`.
     */
    virtual void removeAllProtectedChildren();
    /**
	删除所有受保护节点以及调用cleanup()
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false otherwise.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllProtectedChildrenWithCleanup(bool cleanup);
    
    /**
	受保护节点排序渲染
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     * @param localZOrder Z order for drawing priority. Please refer to setLocalZOrder(int)
     */
    virtual void reorderProtectedChild(Node * child, int localZOrder);
    
    /**
	排序所有受保护节点
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame
     */
    virtual void sortAllProtectedChildren();
    
    /// @} end of Children and Parent
    
    /**
	重写Node:visit(Renderer*,Mat4&,uint32_t),因为需要处理受保护节点渲染。凡是和_protectedChildren受保护节点数组有关的Node函数都需要重写
     * @js NA
     */
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    virtual void cleanup() override;
    
    virtual void onEnter() override;
    
    /** Event callback that is invoked when the Node enters in the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
     * @js NA
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish() override;
    
    /**
     * Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit() override;
    
    /**
     * Event callback that is called every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
     * @js NA
     * @lua NA
     */
    virtual void onExitTransitionDidStart() override;

    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual void disableCascadeColor() override;
    virtual void disableCascadeOpacity()override;
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;
    virtual void setGlobalZOrder(float globalZOrder) override;
CC_CONSTRUCTOR_ACCESS:
    ProtectedNode();
    virtual ~ProtectedNode();
    
protected:
    
    /// helper that reorder a child
    void insertProtectedChild(Node* child, int z);
    
    Vector<Node*> _protectedChildren;        ///< array of children nodes
    bool _reorderProtectedChildDirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ProtectedNode);
};

// end of 2d group
/// @}

NS_CC_END

#endif // __CPROTECTEDCNODE_H__
