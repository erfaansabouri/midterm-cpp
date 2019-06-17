/*
 * Erfan Sabouri Shirazi
 * 9532578
 * AP Exam - Midterm
 * */


#include <iostream>
#include <string>
#include <list>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int max(int x, int y) {
    if (x >= y)
        return x;
    return y;
}


class Iterator {
private:
    int index;

public:
    int get() { return this->index; }

    void set(int val) {
        this->index = val;
    }

    void inc() {
        this->index = this->index + 1;
    }
};


template<class Type>
class Container {
public:
    virtual Type getNumber() = 0;
};


template<class Type>
class Page : public Container<Type> {

private:
    string content;
    Type number;

public:
    Type getNumber() { return number; }
};


template<class Type>
class Section : public Container<Type> {
private:
    int number;
    Page<Type> *pages;

public:
    Type getNumber() { return number; }
};


template<class Type>
class Part : public Container<Type> {
private:
    Section<Type> *sections;
    int count_of_sections;
    int number;
public:
    Type getNumber() override {
        return this->number;
    }

    Part(Section<Type> *array, int count_of_sec, int number) : count_of_sections(count_of_sec), number(number) {
        sections = new Section<Type>[count_of_sections];
        for (int i = 0; i < count_of_sections; i++)
            this->sections[i] = array[i];
    }

    Part<Type> &operator=(Section<Type> *array) {
        sections = new Section<Type>[count_of_sections];
        for (int i = 0; i < count_of_sections; i++)
            this->sections[i] = array[i];
        return *this;

        // or we can call constructor here
    }

    Part &merge(Part &rhs) {
        int max_of_sections = max(this->count_of_sections, rhs.count_of_sections);
        Section<Type> *sections_of_new_part;
        sections_of_new_part = new Part<Type>[max_of_sections];
        int i = 0;
        for (i = 0; i < this->count_of_parts; i++)
            sections_of_new_part[i] = this->parts[i];
        for (int j = i; i < this->count_of_sections + rhs.count_of_sections; j++)
            sections_of_new_part[j] = rhs.parts[i];
        Part *new_part = new Part(sections_of_new_part, max_of_sections, this->number + rhs.number);
        return *new_part;
    }

    Part &operator+(Part &rhs) {
        return merge(rhs);
    }

    Section<Type> &get(int index) {
        return this->sections[index];
    }

    void insert(int index, Section<Type> &newSection) {
        this->sections[index] = newSection;
    }

    Section<Type> &operator[](int index) {
        return sections[index];
    }

    Section<Type> &get_v2(int index) {
        return operator[](index);
    }

    void insert_v2(Section<Type> &newSection, int index) {
        operator[](index) = newSection;
    }

    Section<Type> &operator()(int index) {
        return sections[index];
    }

    Section<Type> &get_v3(int index) {
        return operator()(index);
    }

    void insert_v3(Section<Type> &newSection, int index) {
        operator()(index) = newSection;
    }

    Iterator &begin() {
        Iterator *iter = new Iterator;
        iter->set(0);
        return *iter;
    }

    Iterator &end() {
        Iterator *iter = new Iterator;
        iter->set(count_of_sections);
        return *iter;
    }

    Section<Type> &get_v4(Iterator &iter) {
        return operator[](iter.get());
    }

    void insert_v4(Section<Type> &newPart, Iterator &iter) {
        operator[](iter.get()) = newPart;
    }

    /* Copy and Move constructor */

    Part(const Part &rhs) {
        this->sections = new int[rhs.count_of_sections];
        for (int i = 0; i < rhs.count_of_sections; i++)
            this->sections[i] = rhs.sections[i];
    }

    Part &operator=(const Part &rhs) {
        this->sections = new int[rhs.count_of_sections];
        for (int i = 0; i < rhs.count_of_sections; i++)
            this->sections[i] = rhs.sections[i];

        return *this;
    }


    Part(const Part &&rhs) noexcept {
        this->sections = new int[rhs.count_of_sections];
        for (int i = 0; i < rhs.count_of_sections; i++)
            this->sections[i] = rhs.sections[i];

        rhs.sections = nullptr;
    }


};


class Author : public Container<int> {
public:
    string author_name;
    int id;

    Author(int id, string newName) {
        this->author_name = newName;
        this->id = id;
    }

    int getNumber() override { return id; }
};

class Version : public Container<int> {
public:
    int version;

    explicit Version(int version) {
        this->version = version;
    }

    int getNumber() override { return version; }
};

class Publish_Year : public Container<int> {
public:
    int date;

    explicit Publish_Year(int date) {
        this->date = date;
    }

    int getNumber() override { return date; }
};


template<class Type>
class Book : public Container<Type> {
private:
    string title;
    Part<Type> *parts;
    int count_of_parts;
    Author author;
    Version version;
    Publish_Year publish_year;


public:

    int getNumber() override {
        return this->version.version;
    }

    string getTitle() {
        return this->title;
    }

    void setTitle(string newTitle) {
        this->title = newTitle;
    }

    Book(Part<Type> *array, int count_of_parts, Author author, Publish_Year py) : author(author), publish_year(py) {
        parts = new Part<Type>[count_of_parts];
        for (int i = 0; i < count_of_parts; i++)
            this->parts[i] = array[i];
    }

    Book &operator=(Part<Type> *array) {
        parts = new Part<Type>[count_of_parts];
        for (int i = 0; i < count_of_parts; i++)
            this->parts[i] = array[i];
        return *this;

        // or we can call constructor here
    }

    Part<Type> &get(int index) {
        return this->parts[index];
    }

    void insert(int index, Part<Type> &newPart) {
        this->parts[index] = newPart;
    }

    Part<Type> &operator[](int index) {
        return parts[index];
    }

    Part<Type> &get_v2(int index) {
        return operator[](index);
    }

    void insert_v2(Part<Type> &newPart, int index) {
        operator[](index) = newPart;
    }

    Part<Type> &operator()(int index) {
        return parts[index];
    }

    Part<Type> &get_v3(int index) {
        return operator()(index);
    }

    void insert_v3(Part<Type> &newPart, int index) {
        operator()(index) = newPart;
    }

    Book &merge(Book &rhs) {
        int max_of_parts = max(this->count_of_parts, rhs.count_of_parts);
        Part<Type> *parts_of_new_book;
        parts_of_new_book = new Part<Type>[max_of_parts];
        int i = 0;
        for (i = 0; i < this->count_of_parts; i++)
            parts_of_new_book[i] = this->parts[i];
        for (int j = i; i < this->count_of_parts + rhs.count_of_parts; j++)
            parts_of_new_book[j] = rhs.parts[i];
        Book *new_book = new Book(parts_of_new_book, max_of_parts,
                                  this->author.author_name + " & " + rhs.author.author_name);
        return *new_book;
    }

    Book &operator+(Book &rhs) {
        return merge(rhs);
    }


    /* iterator mode */

    Part<Type> &get_v4(Iterator &iter) {
        return operator[](iter.get());
    }

    void insert_v4(Part<Type> &newPart, Iterator &iter) {
        operator[](iter.get()) = newPart;
    }

    Iterator &begin() {
        Iterator *iter = new Iterator;
        iter->set(0);
        return *iter;
    }

    Iterator &end() {
        Iterator *iter = new Iterator;
        iter->set(count_of_parts);
        return *iter;
    }

    /* Copy and Move constructor */

    Book(const Book &rhs) {
        this->parts = new int[rhs.count_of_parts];
        for (int i = 0; i < rhs.count_of_parts; i++)
            this->parts[i] = rhs.parts[i];
    }

    Book &operator=(const Book &rhs) {
        this->parts = new int[rhs.count_of_parts];
        for (int i = 0; i < rhs.count_of_parts; i++)
            this->parts[i] = rhs.parts[i];

        return *this;
    }


    Book(const Book &&rhs) noexcept {
        this->parts = new int[rhs.count_of_parts];
        for (int i = 0; i < rhs.count_of_parts; i++)
            this->parts[i] = rhs.parts[i];

        rhs.parts = nullptr;
    }


    static list<Book> books;


};


template<class Type>
list<Book<Type>> Book<Type>::books;


class SearchableMedia {
private:
    string *topics;
    string title;
    int count;
public:
    SearchableMedia(string *array, int count_of_topics) : count(count_of_topics) {
        topics = new string[count_of_topics];
        for (int i = 0; i < count_of_topics; i++)
            this->topics[i] = array[i];
    }

    bool search_in_topics(string value) {
        for (int i = 0; i < count; i++) {
            if (this->topics[i] == value) {
                return true;
            }
        }
        return false;
    }

    string getTitle() {
        return title;
    }


};

class SearchableBook : public Book<int>, public SearchableMedia {
public:
    string getTitle() {
        Book::getTitle();
    }
};


int main() {
    return 0;
}
