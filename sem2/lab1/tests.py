import unittest
from lab1 import BinarySearchTree

class TestBinarySearchTree(unittest.TestCase):
    
    def setUp(self):
        self.bst = BinarySearchTree()
        self.bst.build_from_array([50, 30, 70, 20, 40, 60, 80])
    
    def test_insert(self):
        self.bst.insert(25)
        self.assertIn(25, self.bst.inorder())
    
    def test_search_existing(self):
        self.assertIsNotNone(self.bst.search(30))
    
    def test_search_non_existing(self):
        self.assertIsNone(self.bst.search(100))
    
    def test_delete_leaf_node(self):
        self.bst.delete(20)
        self.assertNotIn(20, self.bst.inorder())
    
    def test_delete_node_with_one_child(self):
        self.bst.insert(35)
        self.bst.delete(40)
        self.assertNotIn(40, self.bst.inorder())
        self.assertIn(35, self.bst.inorder())
    
    def test_delete_node_with_two_children(self):
        self.bst.delete(30)
        self.assertNotIn(30, self.bst.inorder())
    
    def test_delete_root(self):
        self.bst.delete(50)
        self.assertNotIn(50, self.bst.inorder())
    
    def test_inorder_traversal(self):
        self.assertEqual(self.bst.inorder(), [20, 30, 40, 50, 60, 70, 80])
    
    def test_insert_duplicate(self):
        self.bst.insert(30)
        self.assertGreaterEqual(self.bst.inorder().count(30), 2)
    
    def test_insert_invalid_data(self):
        with self.assertRaises(TypeError):
            self.bst.insert(None)
    
    def test_delete_invalid_data(self):
        with self.assertRaises(TypeError):
            self.bst.delete(None)

if __name__ == "__main__":
    unittest.main()
