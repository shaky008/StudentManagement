//Utsav Shakya

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//stores all the required data of students
void createBinaryFile(const char *fileName);
void displayBinaryFile(const char *fileName);
void searchStudent(const char *fileName);
void updateStudentInfo(const char *fileName, const char *tempFile);
void deleteData(const char *fileName, const char *tempFile);

struct StudentInfo
{
    char studentId[10];
    char studentName[20];
    char emailId[25];
    char courseId[10];
    char grade;
};

int main()
{
    int choices;
    do
    {
        printf("\n     MAIN MENU    \n");
        printf("1. Create the Binary File\n");
        printf("2. Display the contents of the file\n");
        printf("3. Seek a specific record\n");
        printf("4. Update the contents of a record\n");
        printf("5. Delete a record for the specific name\n");
        printf("6. Exit\n");

        //if entered a string prints invalid result,
        //if number is entered first, and then character, only reads the first enter character(number)
        for(;;)
        {
            printf("Please Enter you choice . . . . \n");
            if (scanf("%d", &choices)== 1)
            {
                break;
            }
            printf("Input was invalid, please try again!\n");

            //discard remainder of line
            for(int c; c = getchar(), c !='\n' && c!= EOF;);
        }


        switch(choices)
        {
        case 1:
            createBinaryFile("studentBinaryFile.bin");
            break;
        case 2:
            displayBinaryFile("studentBinaryFile.bin");
            break;
        case 3:
            searchStudent("studentBinaryFile.bin");
            break;
        case 4:
            updateStudentInfo("studentBinaryFile.bin","temp.bin");
            break;
        case 5:
            deleteData("studentBinaryFile.bin","temp.bin");
            break;
        case 6:
            printf("\nYou are exiting from the program!\n");
            exit(0);
            break;
        }
    }
    while (choices !=6);



    return 0;
}

//creates a binary file and writes data into the file provided by the user
void createBinaryFile(const char *fileName)
{
    //pointer to my file
    FILE *file;

    //number of students
    int studentNo;

    //number of student to add information about at the begining
    printf("enter the number of students you want to add: ");
    scanf("%d", &studentNo);

    //pointer of student ()
    struct StudentInfo *student;

    //allocating memory to pointer student
    student = (struct StudentInfo*)calloc(studentNo, sizeof(struct StudentInfo));

    //prints message if no file does not exist or created
    file = fopen(fileName,"wb");
    if (!file)
    {
        printf("Unable to open file!");
        return;
    }

//    taking information for the number of student user defined
    for(int i =0; i < studentNo; i++)
    {
        //added limits to the pointers to prevent buffer overflow
        printf("Enter Student ID: ");
        scanf("%9s", student[i].studentId);
        printf("Enter Student Name: ");
        scanf("%19s", student[i].studentName);
        printf("Enter Student Email ID: ");
        scanf("%24s", student[i].emailId);
        printf("Enter Student Course ID: ");
        scanf("%9s", student[i].courseId);
        printf("Enter Student Grade: ");
        scanf(" %c", &student[i].grade); // added a space to skip leading whitespace

        //enters the data to the binary files
        fwrite(&student[i], sizeof(struct StudentInfo), 1, file);
        printf("Student added successfully created\n");
    }


    fclose(file);
}

// reads the binary file and displays all the data in the terminal
void displayBinaryFile(const char *fileName)
{
    //pointer to the file
    FILE *file;

    file = fopen(fileName, "rb");
    if (!file)
    {
        printf("Unable to open the file\n");
        return;
    }

    struct StudentInfo student1;

    while (fread(&student1, sizeof(struct StudentInfo), 1, file))
    {
        printf("Student ID: %s\n", student1.studentId);
        printf("Student name: %s\n", student1.studentName);
        printf("Student Email: %s\n", student1.emailId);
        printf("Student course: %s\n", student1.courseId);
        printf("Student grade: %c\n\n", student1.grade);
    }
    fclose(file);
}

//search specific student
void searchStudent(const char *fileName)
{
    FILE *file;

    struct StudentInfo student;

    char studentId[10];

    file = fopen(fileName, "rb");
    if(!file)
    {
        printf("Unable to open file\n");
        return;
    }

    printf("Enter the student's ID: ");
    scanf("%9s", studentId);
    //checks if the id is in binary file or not
    int found = 0;

    //compares the entered student id and the student id in the binary file

    while(fread(&student,sizeof(struct StudentInfo),1,file))
    {
        if(strcmp(student.studentId, studentId) == 0)
        {
            found = 1;
            printf("\nStudent ID: %s\n", student.studentId);
            printf("Student name: %s\n", student.studentName);
            printf("Student Email: %s\n", student.emailId);
            printf("Student course: %s\n", student.courseId);
            printf("Student grade: %c\n\n", student.grade);
        }
    }
    if (!found)
    {
        printf("\nStudent not found");
    }
    fclose(file);
}

//update selected student information
void updateStudentInfo(const char *fileName,const char *tempFile)
{
    //pointer for file and file2
    //file2 is temp file used to update information and paste it in the file later
    FILE *file, *file2;

    struct StudentInfo student;

    //variable to store studentId
    char studentId[10];

    //checks if the file is found or not
    int found = 0;


    file = fopen(fileName,"rb");

    //temp file
    file2 = fopen(tempFile,"wb");

    if(!file)
    {
        printf("file not found!");
        return;
    }

    printf("Enter the student Id to update information\n");
    scanf("%9s", studentId);

    while(fread(&student, sizeof(struct StudentInfo),1,file))
    {
        if(strcmp(studentId, student.studentId) == 0)
        {
            found = 1;
            printf("Enter new Student ID: ");
            scanf("%9s", student.studentId);
            printf("Enter new Student Name: ");
            scanf("%19s", student.studentName);
            printf("Enter new Student Email ID: ");
            scanf("%24s", student.emailId);
            printf("Enter new Student Course ID: ");
            scanf("%9s", student.courseId);
            printf("Enter new Student Grade: ");
            scanf(" %c", &student.grade);

        }

        //writes all the new updated info to file2
        fwrite(&student,sizeof(struct StudentInfo),1, file2);
    }
    fclose(file);
    fclose(file2);


    if (found)
    {
        file2 = fopen(tempFile,"rb");
        file = fopen(fileName,"wb");

        //copies data from file2 to file and replaces the selected studentId information
        while(fread(&student,sizeof(struct StudentInfo),1,file2))
        {
            fwrite(&student,sizeof(struct StudentInfo),1,file);
        }
        printf("Sucessfully updated information");
        fclose(file2);
        fclose(file);
    }
    else
    {
        printf("Student not found");
    }


}

//delete the selected student info
void deleteData(const char *fileName, const char *tempFile)
{
    FILE *file, *file2;

    struct StudentInfo student;

    char studentId[10];
    int found = 0;

    file = fopen(fileName,"rb");
    if (!file)
    {
        printf("No file found\n");
    }

    file2 = fopen(tempFile, "wb");

    printf("Enter the Student ID you want to delete: ");
    scanf("%9s", studentId);

    while(fread(&student, sizeof(struct StudentInfo),1, file))
    {
        if(strcmp(studentId, student.studentId) == 0)
        {
            found = 1;
        }
        else
        {
            fwrite(&student, sizeof(struct StudentInfo),1,file2);
        }
    }
    fclose(file);
    fclose(file2);

    if (found)
    {
        file2 = fopen(tempFile, "rb");
        file = fopen(fileName, "wb");

        while(fread(&student, sizeof(struct StudentInfo),1,file2))
        {
            fwrite(&student, sizeof(struct StudentInfo),1,file);
        }
        fclose(file2);
        fclose(file);
        printf("Sucessfully deleted information");
    }
    else
    {
        printf("student not found\n");
    }

}








