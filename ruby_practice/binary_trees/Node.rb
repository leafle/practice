#!/usr/bin/ruby

class Node

    # binary tree representation
    attr_accessor :value, :left, :right, :parent

    def initialize(value=nil, left=nil, right=nil, parent=nil)
	@value, @left, @right, @parent = value, left, right, parent
    end
end

def insert(node, v, &block)
    # binary tree insert without balancing, 
    # block performs the comparison operation
    return Node.new(v) if not node
    case block[v, node.value]
	when -1 
	    node.left = insert(node.left, v, &block)
	    node.left.parent = node
	when 1 
	    node.right = insert(node.right, v, &block)
	    node.right.parent = node
    end
    return node
end

def visit(n, order=:preorder, &block)
    # visit nodes in a binary tree, order can be determinied
    # block performs visit action
    return false unless (n != nil)

    case order 
	when :preorder 
	    yield n.value
	    visit(n.left, order, &block)
	    visit(n.right, order, &block)
	when :inorder
	    visit(n.left, order, &block)
	    yield n.value
	    visit(n.right, order, &block)
	when :postorder
	    visit(n.left, order, &block)
	    visit(n.right, order, &block)
	    yield n.value
	when :nrinorder
	    printInOrderNR( n, &block )
    end
end

def printInOrderNR ( n, &block )
    curr 	= n
    parents 	= Array.new
    leftNode 	= curr.left
    rightNode 	= curr.right
    parent	= nil

    while curr != nil
	if leftNode != nil
	    parents.push curr
	    curr = leftNode
	    leftNode = curr.left
	    rightNode = curr.right
	else
	    yield curr.value
	    if rightNode != nil
		parents.push curr
		curr = rightNode
		leftNode = curr.left
		rightNode = curr.right
	    else
		parent = parents.pop
		while parent != nil && curr == parent.right
		    curr = parent
		    parent = parents.pop
		end
		curr = parent
		if ( parent != nil )
		    rightNode = curr.right
		end
	    end
	end
    end
end 

begin
    dataArg = ARGV[0]
    orderArg = ARGV[1]
    print $0, ", ", dataArg, ", ", orderArg, "\n"

    if dataArg == nil
	data = "chunkybacon"
    else
	data = dataArg
    end

    if orderArg == ":preorder"
	order = :preorder
    elsif orderArg == ":postorder"
	order = :postorder
    elsif orderArg == ":nrinorder"
	order = :nrinorder
    else
	order = :inorder
    end

    # a simple test case
    root = nil
    data.scan(/./m) {|c| root = insert(root, c) {|a,b| a<=>b}}
    visit(root, order) {|v| print v}
    print "\n"
end
