package com.example

// Error 1: Missing closing brace
class BrokenClass {
    fun method() {
        println("test")
    
// Error 2: Invalid type syntax
fun invalidType(x Int) {
    println(x)
}

// Error 3: Missing colon
class AnotherClass
    val x = 10
}

// Error 4: Invalid assignment
val y = ;

// Error 5: Mismatched parentheses
fun testParen() {
    val list = listOf(1, 2, 3)
    val result = list.map { x -> x * 2 ]
}

// This should still be parsed
object ValidObject {
    const val VERSION = "1.0"
}

// Error 6: Invalid function declaration
fun Int.invalidExtension {
    return this * 2
}

// Error 7: Invalid when statement
fun testWhen(x: Int) {
    when {
        x > 0 -> println("Positive")
        x == 0 println("Zero")
        x < 0 -> println("Negative")
    }
}

interface PartialInterface {
    fun method()
    // Error 8: Property in interface without implementation
    val x: Int
    
    // This is valid
    val y: Int get() = 10
}

// Error 9: Invalid lambda
val lambda = { a b -> a + b }

// This should be valid despite errors above
data class ValidData(val id: Int, val name: String)
