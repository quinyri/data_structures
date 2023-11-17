class Node:
    def __init__(self, data) -> None:
        self.data = data
        self.left = self.right = None

class BinaryTree:
    def __init__(self) -> None:
        self.root = None 

    def __find(self, node, parent, value):
        if node is None:
            return None, parent, False

        if value == node.data:
            return node, parent, True

        if value < node.data:
            return self.__find(node.left, node, value) if node.left else (node, parent, False)
        else:
            return self.__find(node.right, node, value) if node.right else (node, parent, False)

    def append(self, obj):
        if self.root is None:
            self.root = obj
            return self.root

        s, p, fl_find = self.__find(self.root, None, obj.data)

        if not fl_find and s:
            if obj.data < s.data:
                s.left = obj
            else:
                s.right = obj

        return obj

    def print_tree(self, node):
        if node:
            self.print_tree(node.left)
            print(node.data)
            self.print_tree(node.right)

    def print_wide_tree(self, node):
        if node is None:
            return 
        
        list = [node]
        while list:
            new_list = []
            for i in list:
                print(i.data, end=" ")
                if i.left:
                    new_list += [i.left]
                if i.right:
                    new_list += [i.right]

            print()
            list = new_list

    def __del_leaf(self, s, p):
        if p.left == s:
            p.left = None
        elif p.right == s:
            p.right = None

    def __del_one_child(self, s, p):
        child = s.left if s.left else s.right
        if p.left == s:
            p.left = child
        elif p.right == s:
            p.right = child

    def __find_min(self, node, parent):
        return self.__find_min(node.left, node) if node.left else (node, parent)

    def remove(self, key):
        s, p, fl_find = self.__find(self.root, None, key)

        if not fl_find:
            return None
        
        if not s.left and not s.right:
            self.__del_leaf(s, p)
        elif s.left and s.right:
            sr, pr = self.__find_min(s.right, s)
            s.data = sr.data
            self.__del_one_child(sr, pr)
        else:
            self.__del_one_child(s, p)

def main():
    list1 = [10, 5, 7, 16, 13, 2, 20]

    bt = BinaryTree()
    for i in list1:
        bt.append(Node(i))

    bt.remove(5)
    bt.print_wide_tree(bt.root)

if __name__ == "__main__":
    main()
