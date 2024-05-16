package CS284Homework.HW3;
// Yash Yagnik
// I pledge my honor that I have abided by the Stevens Honor System.
//import jdk.incubator.vector.VectorOperators;

import java.util.Scanner;

public class TestTaskList<E>{
    private TaskList<E> toDoList;
    Scanner scan = new Scanner(System.in);

    public TestTaskList() {
        toDoList = new TaskList<E>();
    }

    // creates a TestTaskList object and calls the printMenu method from it
    public static void main(String[] args) {
        TestTaskList<String> test = new TestTaskList<String>();
        test.printMenu();

    }

    // Takes a number from the user which indicates the operation user chooses. From this method, call the helper method processMenuItem(). Repeats printing menu until user enters 8 to quit the program. Check if the user entered values between 1 and 8, if not print an error message and ask for input again.
    public void printMenu(){
        System.out.println("~~~ TO-DO List Program, created by truly yours ~~~");
        boolean x = true;
        int menuItem = 0;
        while(x) {
            if (toDoList.getActive().getSize() == 0){
                System.out.println("==> Currently there are NO items in the To-Do List");
            }
            else{
                System.out.println("Current TO-DO List:\n" +
                        "-------------------");
                toDoList.showActiveTasks();
            }
            System.out.println("To add a new task without priority information, press 1.\nTo add a new task with a priority information, press 2.\nTo cross off the task at the top of the list, press 3.\nTo cross off a certain task in the list, press 4.\nTo see the top 3 highest priority tasks, press 5.\nTo see the completed tasks, press 6.\nTo see the all tasks that has been completed or still active, press 7.\nTo quit the program, press 8.");
            try {
                menuItem = Integer.parseInt(scan.nextLine().strip());
                x = printProcessMenu(menuItem);
            }
            catch (IllegalArgumentException e) {
                System.out.println("ERROR! Please enter a number between 1 and 8 (included).");
                x = true;
            }
        }
        scan.close();
    }

    // calls the appropriate functions based on the input from the user and for each operation from the toDoList object
    public boolean printProcessMenu(int menuItem){

        if (menuItem == 1){
            System.out.println("Please enter the task description:");
            E userTask = (E) scan.nextLine();
            toDoList.createTask(userTask);
            System.out.println("Successfully entered the task to the to-do list!");
            return true;
        }
        else if (menuItem == 2){
            System.out.println("Please enter the task description:");
            String userTask = scan.nextLine();
            System.out.println("Please enter a priority number (1 indicates highest priority, increasing numbers show lower priority) :");
            try {
                int userPriority = Integer.parseInt(scan.nextLine().strip());
                toDoList.createTask((E) userTask, userPriority);
                System.out.println("Successfully entered the task to the to-do list!");
                return true;
            }
            catch (IllegalArgumentException e){
                System.out.println("Unsuccessful operation! Please try again!");
                return true;
            }
        }
        else if (menuItem == 3){
            toDoList.crossOffMostUrgentTask();
            return true;
        }
        else if (menuItem == 4){
            System.out.println("Please enter the task number you would like to cross off the list :");
            try{
                int toRemove = Integer.parseInt(scan.nextLine().strip());
                if (toRemove > toDoList.getActive().getSize() || toRemove <= 0) {
                    System.out.println("Unsuccessful operation! Please try again!");
                    return true;
                }
                toDoList.crossOffTask(toRemove);
                System.out.println("Successfully removed the task number: " + toRemove);
                return true;
            }
            catch (IllegalArgumentException e){
                System.out.println("Unsuccessful operation! Please try again!");
                return true;
            }
        }
        else if (menuItem == 5){
            System.out.println("Top 3 highest priority tasks:\n" +
                    "------------------------------\n" +
                    "Printing Top Three Tasks...");
            toDoList.printTopThree();
            return true;
        }
        else if (menuItem == 6){
            System.out.println("Completed Tasks:\n" +
                    "----------------");
            toDoList.showCompletedTasks();
            return true;
        }
        else if (menuItem == 7){
            System.out.println("All of the Tasks - Both completed and active:\n" +
                    "---------------------------------------------");
            toDoList.showAllTasks();
            return true;
        }
        else if (menuItem == 8){
            return false;
        }
        else{
            System.out.println("ERROR! Please enter a number between 1 and 8 (included).");
            return true;
        }

    }


}
