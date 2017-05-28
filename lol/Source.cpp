//Удалить из левой ветви дерева узел с максимальным значением ключа и все связанные с ним узлы.
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
	info key; //ключ
	TreeNode* left; //указатель на левого потомка
	TreeNode* right; //указатель на правого потомка
	TreeNode* parent; //указатель на родительский узел
};

//структура "бинарное дерево поиска" - BinarySearchTree, BST
struct BST {
	TreeNode* root; //указатель на корневой узел дерева
};

//функция "посещения" узла - вывод на экран его ключа
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
        insertNode(tree, value); //вызов функции добавления узла
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
	int *intArray = new int[num]; //создание массива значений
								  //заполнение массива значений вручную
	for (int i = 0; i < num; i++)
	{
		cout << "№" << i << " el. - ";
		cin >> intArray[i]; 
	}
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - i - 1; j++)
		{
			if (intArray[i] > intArray[j]) { 		// Переставляем элементы
				int r = intArray[i];
				intArray[i] = intArray[j];
				intArray[j] = r;
			}
		}
	}
	Make_Blns( tree->root, 0, num, intArray);
	cout << "New tree has been created..." << endl;
	return createTreeFromArray(intArray, num); //возвращает указатель на новое созданное дерево
	delete[]intArray;

}

void insertNode(BST* tree, int keyValue)
{
	//создание двух подвижных указателей, следующих друг за другом в виде родитель-потомок
	TreeNode* parent = NULL;
	TreeNode* ptr = tree->root;
	bool find = true;
	//поиск подходящего места для вставляемого узла
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

		//непосредственно создание вставляемого узла
		TreeNode* newNode = new TreeNode;
		newNode->key.number = keyValue;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->parent = parent;

		if (parent == NULL)
			tree->root = newNode; //вставленный узел - корневой
		else
		{
			if (newNode->key.number < parent->key.number) {
				parent->left = newNode;
			}  //...левый

			else
				parent->right = newNode; //...правый
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
//поиск узла
//возвращает указатель на найденный узел
//если узел не найден, возвращает нулевой указатель

TreeNode* searchNode(TreeNode* node, int keyValue)
{
	//условие окончание поиск - узел отсутствует, либо найден
	if (node == NULL || node->key.number == keyValue)
		return node;

	if (keyValue > node->key.number)
		searchNode(node->right, keyValue); //поиск в правом поддереве
	else
		searchNode(node->left, keyValue); //...в левом
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
	int *intArray = new int[num]; //создание массива значений

	cout << "Enter the elements randomly(1) or manually(2): ";
	while (choice != 1 && choice != 2)
	{
		cin >> choice;
		switch (choice)
		{
			//заполнение массива значений случайными числами
		case 1: {
			for (int i = 0; i < num; i++)
			{
				intArray[i] = rand() % 100 + 1;
			}
			break;
		}
				//заполнение массива значений вручную
		case 2: {
			for (int i = 0; i < num; i++)
			{
				cout << "№" << i << " el. - ";
				cin >> intArray[i];
			}
			break;
		}
		default: cout << "1 or 2, please";
		}
	}
	cout << "New tree has been created..." << endl;
return createTreeFromArray(intArray, num); //возвращает указатель на новое созданное дерево
delete[]intArray;
}

 //Удаление дерева
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

//Просмотр (чтобы норм)
void View(TreeNode* node, int level) {
	string str;
	if (node) {
		View(node->right, level + 1);
		for (int i = 0; i<level; i++) str = str + "    ";
		cout << str << node->key.number << endl;
		View(node->left, level + 1);
	}
}

	//удаление узла 
	//возвращает true, если удаление успешно, возвращает false, если удаляемый узел не существует
void option2(BST* tree)
{
	int value = 0;
	cout << endl << "Node deletion..." << endl;
	cout << "Enter the key value of the node to delete: ";
	cin >> value;
	if (deleteNode(tree, searchNode(tree->root, value)) == false) //вызов функции удаления узла
		cout << "Node can't be deleted!" << endl;
	else
		cout << "Node has been deleted." << endl;
}

bool deleteNode(BST* tree, TreeNode* node)
{
	//если удаляемый узел не существует, завершает функцию
	if (node == NULL)
		return false;

	//проверяем, является ли удаляемый узел корнем дерева
	bool isRoot = false;
	if (node->parent == NULL)
		isRoot = true;

	//первый случай - удаление листа
	if (node->left == NULL && node->right == NULL)
	{
		if (isRoot)
		{
			tree->root = NULL;
		}
		else
		{
			if (node->parent->left == node) //удаляемый узел - левый сын
				node->parent->left = NULL;
			else							//...правый сын
				node->parent->right = NULL;
			node->parent = NULL;
		}
	}

	//второй случай - узел имеет одного потомка
	else
	{
		if (node->left == NULL || node->right == NULL)
		{
			if (node->left == NULL) //узел имеет правого потомка
			{
				if (!isRoot)
				{
					if (node->parent->left == node) //удаляемый узел - левый сын
						node->parent->left = node->right;
					else							//...правый сын
						node->parent->right = node->right;
				}
				node->right->parent = node->parent;
				if (isRoot)
				{
					tree->root = node->right;
				}
				node->parent = NULL; node->right = NULL;
			}
			else				//узел имеет левого потомка
			{
				if (!isRoot)
				{
					if (node->parent->left == node) //удаляемый узел - левый сын
						node->parent->left = node->left;
					else							//...правый сын
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

	//третий случай - узел имеет обоих потомков
	if (node->left != NULL && node->right != NULL)
	{
		TreeNode* successor = findSuccessor(node); //ищем узел, следующий за удаляемым (succ)

		if (successor->parent->left == successor) //succ - левый сын
		{
			successor->parent->left = successor->right;
			if (!isRoot)
			{
				if (node->parent->right == node)	//удаляемый узел - левый сын
					node->parent->right = successor;
				else							//...правый сын
					node->parent->left = successor;
			}
			if (successor->right != NULL)
				successor->right->parent = successor->parent;
		}
		else									 //succ - правый сын
		{
			successor->parent->right = successor->right;
			if (!isRoot)
			{
				if (node->parent->right == node)	//удаляемый узел - левый сын
					node->parent->right = successor;
				else							//...правый сын
					node->parent->left = successor;
			}
			if (successor->right != NULL)
				successor->right->parent = successor->parent;
		}

		//помещение succ на место удаляемого узла
		node->left->parent = successor;
		node->right->parent = successor;
		successor->left = node->left;
		successor->right = node->right;

		//помещение succ на место корневого узла
		if (isRoot)
		{
			tree->root = successor;
			successor->parent = NULL;
		}
	}

	//обнуление указателей удаляемого узла
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	delete node;
	return true;
}

TreeNode* findSuccessor(TreeNode* node)
{
	if (node->right != NULL)
		return minElement(node->right); //если у узла существует правое поддерево, то его минимальный узел является искомым узлом
	else
	{
		TreeNode* parentNode = node->parent; //иначе, начиная с родителя и выше по дереву, ищем ближайший узел, являющийся правым потомком своего родителя
		while (parentNode != NULL && node == parentNode->right)
		{
			node = parentNode;
			parentNode = node->parent;
		}
		return parentNode;
	}
}

//поиск узла с максимальным значением ключа
//переход к крайне правому узлу в дереве

TreeNode* maxElement(TreeNode* node)
{
	while (node->right != NULL)
		node = node->right;
	return node;
}

//поиск узла с минимальным значением ключа
//переход к крайне левому узлу в дереве

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
		return maxElement(node->left); //если у узла существует правое поддерево, то его максимальный узел является искомым узлом
}

void option(BST* tree)
{
	Task(tree, tree->root);
}