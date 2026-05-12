package com.example

class Person(val name: String, val age: Int) {
    fun greet() {
        println("Hello, I am $name and I am $age years old")
    }
    
    fun isAdult(): Boolean = age >= 18
}

class Employee(name: String, age: Int, val salary: Double) : Person(name, age) {
    fun giveSalary() {
        println("Employee $name earns $salary")
    }
}
