using System;
using Lib;

namespace ProjectWithLib
{
    class Program
    {
        static void Main()
        {
            Random random = new Random();
            MyList<int> list1 = new MyList<int>();
            MyList<int> list2 = new MyList<int>();


            int size1 = random.Next(5, 20);
            int size2 = random.Next(5, 20);
            for (int i = 0; i < size1; i++)
            {
                list1.Add(random.Next(1, 20));
            }
            for (int i = 0; i < size2; i++)
            {
                list2.Add(random.Next(1, 20));
            }

            Console.WriteLine($"Initial List 1 (Size: {size1}):");
            list1.print();
            Console.WriteLine($"Initial List 2 (Size: {size2}):");
            list2.print();

            while (true)
            {
                Console.WriteLine("Select an action:");
                Console.WriteLine("1 - Add element");
                Console.WriteLine("2 - Add first element");
                Console.WriteLine("3 - Search element");
                Console.WriteLine("4 - Remove element");
                Console.WriteLine("5 - Sort");
                Console.WriteLine("6 - Find intersection");
                Console.WriteLine("7 - Merge");
                Console.WriteLine("8 - View");
                Console.WriteLine("9 - Exit");

                int choice = Convert.ToInt32(Console.ReadLine());

                if (choice >= 1 && choice <= 5)
                {
                    Console.WriteLine("Select the list (1 or 2): ");
                    int listChoice = Convert.ToInt32(Console.ReadLine());
                    MyList<int> selectedList;

                    if (listChoice == 2)
                        selectedList = list2;

                    else
                        selectedList = list1;


                    switch (choice)
                    {
                        case 1:
                            Console.Write("Enter number to add: ");
                            int addNum = Convert.ToInt32(Console.ReadLine());
                            selectedList.Add(addNum);
                            Console.Write("Updated List: ");
                            selectedList.print();
                            break;




                        case 2:
                            Console.Write("Enter number to add first: ");
                            int addFirstNum = Convert.ToInt32(Console.ReadLine());
                            selectedList.AddFirst(addFirstNum);
                            Console.Write("Updated List: ");
                            selectedList.print();
                            break;

                        case 3:
                            Console.Write("Enter number to search: ");
                            int searchNum = Convert.ToInt32(Console.ReadLine());
                            if (selectedList.search(searchNum))
                                Console.WriteLine("Number found!");
                            else
                                Console.WriteLine("Number not found.");
                            break;

                        case 4:
                            Console.Write("Enter number to remove: ");
                            int removeNum = Convert.ToInt32(Console.ReadLine());
                            if (selectedList.RemoveElement(removeNum))
                                Console.WriteLine("Number removed successfully.");
                            else
                                Console.WriteLine("Number not found in the list.");
                            break;

                        case 5:
                            Console.Write("Sorting list...");
                            selectedList.SortMintoMax();
                            selectedList.print();
                            break;
                    }
                }
                else
                {
                    switch (choice)
                    {

                        case 6:
                            MyList<int> intersection = list1.FindIntersection(list1, list2);
                            Console.WriteLine("Intersection of List 1 and List 2:");
                            intersection.print();
                            break;

                        case 7:
                            list1.mergeList(list1, list2);
                            Console.WriteLine("Merged List:");
                            list1.print();
                            break;

                        case 8:
                            list1.print();
                            list2.print();
                            break;

                        case 9:
                            Console.WriteLine("Exiting...");
                            return;

                        default:
                            Console.WriteLine("Invalid choice. Please try again.");
                            break;
                    }
                }
            }
        }
    }
}