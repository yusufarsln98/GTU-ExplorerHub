package lib.binarysearchtreetoavltree;

public class BinarySearchTreeWithRotate<E extends Comparable<E>> extends BinarySearchTree<E> {
    
    private static boolean BALANCED;

    /**
     * Take a binary search tree, and convert it into an AVL tree
     * which is balanced.
     * @return
     */
    public BinarySearchTreeWithRotate<E> toAVLTree()
    {
        // In some very rare cases, the tree will not be balanced in 
        // first place. Therefore, be sure that if it is balanced
        // by keeping track of boolean BALANCED value.
        while (!BALANCED){
            BALANCED = true;
            root = toAVLTree(root);
        }
        return this;
    }

    /**
     * If the tree is not balanced, then we will find if the tree is a left-left, left-right,
     * right-left, or right-right tree. If the tree is a left-left or right-right tree, then we will
     * rotate the parent to the right or left. If the tree is a left-right or right-left tree, then we
     * will rotate the child to the left or right, and then rotate the parent to the right or left.
     * 
     * @param localRoot The root of the tree.
     * @return The root of the tree.
     */
    private Node<E> toAVLTree(Node<E> localRoot) 
    {
        if (localRoot == null) {
            // If the tree is empty, then it is balanced.
            return null;
        }
        else
        {
            // If the tree is not empty, then we need to check if it is balanced.
            // Check for the left, then the right subtrees.
            // In each level, find the height of the left and right subtrees.
            
            localRoot.left = toAVLTree(localRoot.left);
            localRoot.right = toAVLTree(localRoot.right);

            int rightHeight = 0;
            int leftHeight = 0;

            if (localRoot.right != null)
                rightHeight = height(localRoot.right);
            
            if (localRoot.left != null)
                leftHeight = height(localRoot.left);

            // If the difference is greater than 1, then the tree is not balanced.
            if (Math.abs(rightHeight - leftHeight) > 1) {
                // Once we find that the tree is not balanced, we will set the BALANCED value to false
                // to check the tree again.
                BALANCED = false;
                // If the tree is unbalanced, then we need to find if tree is,
                // left-left, left-right, right-left, or right-right tree.
                int rightChildHeight = 0;
                int leftChildHeight = 0;
                
                // If tree is right tree.
                if (rightHeight > leftHeight) 
                {
                    Node<E> rightChild = localRoot.right;
                    // Find the height of the right and left child.
                    if (rightChild.right != null)
                        rightChildHeight = height(rightChild.right);
                    if (rightChild.left != null)
                        leftChildHeight = height(rightChild.left);
                    
                    // If tree is right-left tree, then we need to rotate child to the right,
                    // and then rotate the parent to the left.
                    if (leftChildHeight > rightChildHeight)
                    {
                        localRoot.right = rotateRight(rightChild);
                        return rotateLeft(localRoot);
                    }
                    // If tree is right-right tree, then we just need to rotate the parent to the left.
                    else
                    {
                        return rotateLeft(localRoot);
                    }
                }
                // If tree is left tree.
                else
                {
                    Node<E> leftChild = localRoot.left;
                    // Find the height of the right and left child.
                    if (leftChild.right != null)
                        rightChildHeight = height(leftChild.right);
                    if (leftChild.left != null)
                        leftChildHeight = height(leftChild.left);
                    
                    // If tree is left-right tree, then we need to rotate child to the left,
                    // and then rotate the parent to the right.
                    if (rightChildHeight > leftChildHeight)
                    {
                        localRoot.left = rotateLeft(leftChild);
                        return rotateRight(localRoot);
                    }
                    // If tree is left-left tree, then we just need to rotate the parent to the right.
                    else
                    {
                        return rotateRight(localRoot);
                    }
                }
            }
            // If the tree is balanced, then we will return the root of the tree.
            else
            {
                return localRoot;
            }
        }
    }


    // Methods 
    /** Method to perform a right rotation. 
     * @pre root is the root of a binary search tree. 
     * @post root.right is the root of a binary search tree, 
     * root.right.right is raised one level, root.right.left does not change levels, 
     * root.left is lowered one level, the new root is returned. 
     * @param root The root of the binary tree to be rotated 
     * @return The new root of the rotated tree
     */
    protected Node<E> rotateRight(Node<E> root) 
    { 
        Node<E> temp = root.left; 
        root.left = temp.right; 
        temp.right = root; 
        return temp;
    }

    /** Method to perform a left rotation.
     * @pre root is the root of a binary search tree.
     * @post root.left is the root of a binary search tree,
     * root.left.left is raised one level, root.left.right does not change levels,
     * root.right is lowered one level, the new root is returned.
     * @param root The root of the binary tree to be rotated
     * @return The new root of the rotated tree
     */
    public Node<E> rotateLeft(Node<E> root)
    {
        Node<E> temp = root.right;
        root.right = temp.left;
        temp.left = root;
        return temp;
    }



    /**
     * Return 1 + the furthest depth of the left or right subtree.
     * 
     * @param node The node to start at.
     * @return The height of the tree.
     */
    private int height(Node<E> node)
    {
        if (node == null)
            return 0;
        
        // Return 1 + max(the height of the left or right subtrees)
        return (1 + Math.max(height(node.left),
                             height(node.right)));
    }

}
