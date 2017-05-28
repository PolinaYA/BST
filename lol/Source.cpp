//������� �� ����� ����� ������ ���� � ������������ ��������� ����� � ��� ��������� � ��� ����.
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string>
#include <math.h>

using namespace std;

struct info {
	int number;
	char FIO;
};

struct TreeNode {
	info key; //����
	TreeNode* left; //��������� �� ������ �������
	TreeNode* right; //��������� �� ������� �������
	TreeNode* parent; //��������� �� ������������ ����
};

//��������� "�������� ������ ������" - BinarySearchTree, BST
struct BST {
	TreeNode* root; //��������� �� �������� ���� ������
};

//������� "���������" ���� - ����� �� ����� ��� �����
void printNode(TreeNode* node)
{
	cout << node->key.number << " ";
}

void workMenu();
void insertNode(BST* tree, int keyValue);
TreeNode* searchNode(TreeNode* node, int keyValue);
void particular_node(BST* tree, int value);
void find_node_option(BST* tree);
BST* option5();
BST* createTreeFromArray(int* arr, int number);
void Make_Blns(TreeNode* node, int n, int k, int *a);
void View(TreeNode* node, int level);
TreeNode* findSuccessor(TreeNode* node);
bool deleteNode(BST* tree, TreeNode* node);
TreeNode* maxElement(TreeNode* node);
TreeNode* minElement(TreeNode* node);
void option2(BST* tree);
void Task();
void Del_All(TreeNode* node);
BST* lol();
void option(BST* tree);
TreeNode* feature(TreeNode* node);


int main() {
	srand(time(0));
	workMenu();
	return 0;

}

void workMenu(){
BST* tree = new BST;
tree->root = NULL;
void(*funptr)(TreeNode*) = printNode;
int value = 0;
while (true)
{
	int choice = 0;
	cout << endl << "<<<<<<<<<<<<<<<<<<" << endl;
	cout << "Menu:" << endl;
	cout << "1. Add new node" << endl;
	cout << "2. Delete node" << endl;
	cout << "3. View Tree " << endl;
	cout << "4. Node search" << endl;
	cout << "5. Create tree from array" << endl;
	cout << "6. Balanced tree" << endl;
	cout << "7. Clear screen" << endl;
	cout << "8. Task" << endl;
	cout << "9. Exit" << endl;
	cout << "<<<<<<<<<<<<<<<<<<" << endl;
	cout << endl << "Your choice: ";
	cin >> choice;
	switch (choice)
	{
	case 7:
		system("cls");
		break;
	case 8:
		option(tree);
		break;
	case 9:
		cout << endl << "Ending working session..." << endl;
		Del_All(tree->root);
		return;
		break;
	default:
		cout << endl << "From 1 to 8, please..." << endl;

	case 1:                                                  //work
		cout << endl << "Node inserting..." << endl;
		cout << "Enter the key value of inserting node: ";
		cin >> value;
        insertNode(tree, value); //����� ������� ���������� ����
		//cout << "New node has been inserted." << endl;
		break;
	case 2:
		option2(tree);
		break;
	case 3:
		View(tree->root, 0);                               //work
		break;
	case 4:
		find_node_option(tree);                               //work
		break;
	case 5:
		tree = option5();
		break;
	case 6:
		cout << "Balanced tree" << endl;
		tree = lol();
		
            break;
	
	}
}
}


BST* lol() {
	BST* tree = new BST;
	int num = 0, choice = 0;
	cout << endl << "Tree generating..." << endl;
	cout << "Enter the number of elements: ";
	cin >> num;
	int *intArray = new int[num]; //�������� ������� ��������
								  //���������� ������� �������� �������
	for (int i = 0; i < num; i++)
	{
		cout << "�" << i << " el. - ";
		cin >> intArray[i]; 
	}
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - i - 1; j++)
		{
			if (intArray[i] > intArray[j]) { 		// ������������ ��������
				int r = intArray[i];
				intArray[i] = intArray[j];
				intArray[j] = r;
			}
		}
	}
	Make_Blns( tree->root, 0, num, intArray);
	cout << "New tree has been created..." << endl;
	return createTreeFromArray(intArray, num); //���������� ��������� �� ����� ��������� ������
	delete[]intArray;

}

void insertNode(BST* tree, int keyValue)
{
	//�������� ���� ��������� ����������, ��������� ���� �� ������ � ���� ��������-�������
	TreeNode* parent = NULL;
	TreeNode* ptr = tree->root;
	bool find = true;
	//����� ����������� ����� ��� ������������ ����
	while (ptr != NULL && find)
	{
		parent = ptr;
		if (keyValue == ptr->key.number) {
			find = false;
			cout << "Dublucate Key!";
		}
		if (keyValue < ptr->key.number)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}

	if (find) {

		//��������������� �������� ������������ ����
		TreeNode* newNode = new TreeNode;
		newNode->key.number = keyValue;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->parent = parent;

		if (parent == NULL)
			tree->root = newNode; //����������� ���� - ��������
		else
		{
			if (newNode->key.number < parent->key.number) {
				parent->left = newNode;
			}  //...�����

			else
				parent->right = newNode; //...������
		}
	}
}

void find_node_option(BST* tree) {
	int value = 0;
	cout << endl << "Node searching..." << endl;
	if (tree->root == NULL)
	{
		cout << "Tree is empty!" << endl;
		return;
	}
	cout << "Enter the key value of the node to find: ";
	cin >> value;
	TreeNode* foundedNode = searchNode(tree->root, value);
	if (foundedNode == NULL)
		cout << "Node doesn't belong to tree!";
	else
		cout << "Node has been found." << endl;

}
//����� ����
//���������� ��������� �� ��������� ����
//���� ���� �� ������, ���������� ������� ���������

TreeNode* searchNode(TreeNode* node, int keyValue)
{
	//������� ��������� ����� - ���� �����������, ���� ������
	if (node == NULL || node->key.number == keyValue)
		return node;

	if (keyValue > node->key.number)
		searchNode(node->right, keyValue); //����� � ������ ���������
	else
		searchNode(node->left, keyValue); //...� �����
}

void particular_node(BST* tree, int value) {
	//int value = 0;
	cout << endl << "Node searching..." << endl;
	if (tree->root == NULL)
	{
		cout << "Tree is empty!" << endl;
		return;
	}
	cout << "Enter the key value of the node to find: ";
	cin >> value;
	TreeNode* foundedNode = searchNode(tree->root, value);
	if (foundedNode == NULL)
		cout << "Node doesn't belong to tree!";
	else
		cout << "Node has been found." << endl;
	
}

BST* createTreeFromArray(int* arr, int number)
{
	BST* tree = new BST;
	tree->root = NULL;
	for (int i = 0; i < number; i++)
	{
		insertNode(tree, arr[i]);
	}
	return tree;
}

 BST* option5()
{
	int num = 0, choice = 0;
	cout << endl << "Tree generating..." << endl;
	cout << "Enter the number of elements: ";
	cin >> num;
	int *intArray = new int[num]; //�������� ������� ��������

	cout << "Enter the elements randomly(1) or manually(2): ";
	while (choice != 1 && choice != 2)
	{
		cin >> choice;
		switch (choice)
		{
			//���������� ������� �������� ���������� �������
		case 1: {
			for (int i = 0; i < num; i++)
			{
				intArray[i] = rand() % 100 + 1;
			}
			break;
		}
				//���������� ������� �������� �������
		case 2: {
			for (int i = 0; i < num; i++)
			{
				cout << "�" << i << " el. - ";
				cin >> intArray[i];
			}
			break;
		}
		default: cout << "1 or 2, please";
		}
	}
	cout << "New tree has been created..." << endl;
return createTreeFromArray(intArray, num); //���������� ��������� �� ����� ��������� ������
delete[]intArray;
}

 //�������� ������
 void Del_All(TreeNode* node) {
	 if (node != NULL) {
		 Del_All(node->left);
		 Del_All(node->right);
		 delete node;
	 }
 }

void Make_Blns(TreeNode* node, int n, int k, int *a) {
	if (n == k) {
		node = NULL;
		return;
	}
	else {
		int m = (n + k) / 2;
		TreeNode* newNode = new TreeNode;
		//*p = new Tree;BST* tree = new BST;
		newNode->key.number = a[m];
		Make_Blns(newNode->left, n, m, a);
		Make_Blns(newNode->right, m + 1, k, a);
	}
}

//�������� (����� ����)
void View(TreeNode* node, int level) {
	string str;
	if (node) {
		View(node->right, level + 1);
		for (int i = 0; i<level; i++) str = str + "    ";
		cout << str << node->key.number << endl;
		View(node->left, level + 1);
	}
}

	//�������� ���� 
	//���������� true, ���� �������� �������, ���������� false, ���� ��������� ���� �� ����������
void option2(BST* tree)
{
	int value = 0;
	cout << endl << "Node deletion..." << endl;
	cout << "Enter the key value of the node to delete: ";
	cin >> value;
	if (deleteNode(tree, searchNode(tree->root, value)) == false) //����� ������� �������� ����
		cout << "Node can't be deleted!" << endl;
	else
		cout << "Node has been deleted." << endl;
}

bool deleteNode(BST* tree, TreeNode* node)
{
	//���� ��������� ���� �� ����������, ��������� �������
	if (node == NULL)
		return false;

	//���������, �������� �� ��������� ���� ������ ������
	bool isRoot = false;
	if (node->parent == NULL)
		isRoot = true;

	//������ ������ - �������� �����
	if (node->left == NULL && node->right == NULL)
	{
		if (isRoot)
		{
			tree->root = NULL;
		}
		else
		{
			if (node->parent->left == node) //��������� ���� - ����� ���
				node->parent->left = NULL;
			else							//...������ ���
				node->parent->right = NULL;
			node->parent = NULL;
		}
	}

	//������ ������ - ���� ����� ������ �������
	else
	{
		if (node->left == NULL || node->right == NULL)
		{
			if (node->left == NULL) //���� ����� ������� �������
			{
				if (!isRoot)
				{
					if (node->parent->left == node) //��������� ���� - ����� ���
						node->parent->left = node->right;
					else							//...������ ���
						node->parent->right = node->right;
				}
				node->right->parent = node->parent;
				if (isRoot)
				{
					tree->root = node->right;
				}
				node->parent = NULL; node->right = NULL;
			}
			else				//���� ����� ������ �������
			{
				if (!isRoot)
				{
					if (node->parent->left == node) //��������� ���� - ����� ���
						node->parent->left = node->left;
					else							//...������ ���
						node->parent->right = node->left;
				}
				node->left->parent = node->parent;
				if (isRoot)
				{
					tree->root = node->left;
				}
				node->parent = NULL; node->left = NULL;
			}
		}
	}

	//������ ������ - ���� ����� ����� ��������
	if (node->left != NULL && node->right != NULL)
	{
		TreeNode* successor = findSuccessor(node); //���� ����, ��������� �� ��������� (succ)

		if (successor->parent->left == successor) //succ - ����� ���
		{
			successor->parent->left = successor->right;
			if (!isRoot)
			{
				if (node->parent->right == node)	//��������� ���� - ����� ���
					node->parent->right = successor;
				else							//...������ ���
					node->parent->left = successor;
			}
			if (successor->right != NULL)
				successor->right->parent = successor->parent;
		}
		else									 //succ - ������ ���
		{
			successor->parent->right = successor->right;
			if (!isRoot)
			{
				if (node->parent->right == node)	//��������� ���� - ����� ���
					node->parent->right = successor;
				else							//...������ ���
					node->parent->left = successor;
			}
			if (successor->right != NULL)
				successor->right->parent = successor->parent;
		}

		//��������� succ �� ����� ���������� ����
		node->left->parent = successor;
		node->right->parent = successor;
		successor->left = node->left;
		successor->right = node->right;

		//��������� succ �� ����� ��������� ����
		if (isRoot)
		{
			tree->root = successor;
			successor->parent = NULL;
		}
	}

	//��������� ���������� ���������� ����
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	delete node;
	return true;
}

TreeNode* findSuccessor(TreeNode* node)
{
	if (node->right != NULL)
		return minElement(node->right); //���� � ���� ���������� ������ ���������, �� ��� ����������� ���� �������� ������� �����
	else
	{
		TreeNode* parentNode = node->parent; //�����, ������� � �������� � ���� �� ������, ���� ��������� ����, ���������� ������ �������� ������ ��������
		while (parentNode != NULL && node == parentNode->right)
		{
			node = parentNode;
			parentNode = node->parent;
		}
		return parentNode;
	}
}

//����� ���� � ������������ ��������� �����
//������� � ������ ������� ���� � ������

TreeNode* maxElement(TreeNode* node)
{
	while (node->right != NULL)
		node = node->right;
	return node;
}

//����� ���� � ����������� ��������� �����
//������� � ������ ������ ���� � ������

TreeNode* minElement(TreeNode* node)
{
	while (node->left != NULL)
		node = node->left;
	return node;
}

void Task(BST* tree ,TreeNode* node) { 

	cout << endl << "Node searching..." << endl;
	if (tree->root == NULL)
	{
		cout << "Tree is empty!" << endl;
		return;
	}

	TreeNode* result = feature(tree->root);
	deleteNode(tree, result);
	cout<<"it's work!" << endl;

}

TreeNode* feature(TreeNode* node)
{
	if (node->left != NULL)
		return maxElement(node->left); //���� � ���� ���������� ������ ���������, �� ��� ������������ ���� �������� ������� �����
}

void option(BST* tree)
{
	Task(tree, tree->root);
}