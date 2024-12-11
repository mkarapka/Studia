class Trie:
    is_end: bool
    children: dict[str, "Trie"]

    def __init__(self):
        self.is_end = False
        self.children = {}

    def search(self, s):
        node = self
        for ch in s:
            if ch not in node.children:
                return None
            node = node.children[ch]
        return node if node.is_end else None

    def search_by_letter(self, s, letter):
        node = self.search(letter)
        if node is None:
            return None
        return node.search(s)

    def insert(self, s):
        node = self
        for ch in s:
            if ch not in node.children:
                node.children[ch] = Trie()
            node = node.children[ch]
        node.is_end = True

    def print_all_nodes(self, prefix=""):
        if self.is_end:
            print(prefix)
        for head, child in self.children.items():
            child.print_all_nodes(prefix + head)
