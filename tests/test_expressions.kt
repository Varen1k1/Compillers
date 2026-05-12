package com.example

fun testExpressions() {
    // Arithmetic expressions
    val sum = 10 + 20 * 30 / 4 - 5
    val mod = 17 % 5
    val power = 2 power 8
    
    // Comparison expressions
    val isGreater = 5 > 3
    val isEqual = 10 == 10
    val notEqual = 5 != 3
    
    // Logical expressions
    val and = true && false
    val or = true || false
    val not = !true
    
    // Null safety
    val name: String? = "Kotlin"
    val length = name?.length
    val safeLength = name?.length ?: 0
    val forceLength = name!!.length
    
    // Range expressions
    val range1 = 1..10
    val range2 = 1..<10
    val inRange = 5 in range1
    val notInRange = 15 !in range2
    
    // Type checking and casting
    val obj: Any = "Hello"
    val isString = obj is String
    val notInt = obj !is Int
    val casted = obj as String
    val safeCast = obj as? String
    
    // Collections
    val list = listOf(1, 2, 3, 4, 5)
    val mapped = list.map { it * 2 }
    val filtered = list.filter { it > 2 }
    val firstEven = list.find { it % 2 == 0 }
    
    // String interpolation
    val x = 10
    val y = 20
    val message = "x = $x, y = $y, sum = ${x + y}"
    
    // Lambdas
    val add: (Int, Int) -> Int = { a, b -> a + b }
    val result = add(5, 3)
    
    // Method references
    val stringLength: (String) -> Int = String::length
    val constructor = ::Person
    
    // If expression
    val maxValue = if (10 > 5) 10 else 5
    val category = if (x < 10) "small" else if (x < 20) "medium" else "large"
    
    // When expression
    val grade = when (x) {
        in 0..40 -> "F"
        in 41..60 -> "D"
        in 61..75 -> "C"
        in 76..90 -> "B"
        in 91..100 -> "A"
        else -> "Invalid"
    }
    
    val typeDesc = when (obj) {
        is String -> "String: ${obj.length}"
        is Int -> "Integer: $obj"
        else -> "Unknown type"
    }
}

class Person(val name: String, val age: Int)
