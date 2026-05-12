package com.example

fun controlFlowExamples() {
    // If statement
    val x = 10
    if (x > 0) {
        println("Positive")
    } else if (x < 0) {
        println("Negative")
    } else {
        println("Zero")
    }
    
    // For loop
    for (i in 1..10) {
        if (i % 2 == 0) continue
        if (i > 8) break
        println(i)
    }
    
    // For loop with range
    for (i in 1 until 10) {
        println(i)
    }
    
    // For loop with array
    val arr = intArrayOf(1, 2, 3, 4, 5)
    for (item in arr) {
        println(item)
    }
    
    // For loop with index
    val list = listOf("a", "b", "c")
    for ((index, value) in list.withIndex()) {
        println("$index: $value")
    }
    
    // While loop
    var counter = 0
    while (counter < 10) {
        counter++
        println(counter)
    }
    
    // Do-while loop
    do {
        println("At least once")
    } while (false)
    
    // When statement
    val day = 3
    when (day) {
        1 -> println("Monday")
        2 -> println("Tuesday")
        3 -> println("Wednesday")
        in 4..6 -> println("Workday")
        else -> println("Weekend")
    }
    
    // Try-catch
    try {
        val result = "10".toInt()
        println(result)
    } catch (e: NumberFormatException) {
        println("Invalid number")
    } catch (e: Exception) {
        println("General error: ${e.message}")
    } finally {
        println("Cleanup")
    }
    
    // Try-catch as expression
    val parsed = try {
        "abc".toInt()
    } catch (e: NumberFormatException) {
        -1
    }
    
    // Throw statement
    if (x < 0) {
        throw IllegalArgumentException("x must be positive")
    }
    
    // Label with break
    outerLoop@ for (i in 1..10) {
        for (j in 1..10) {
            if (i * j == 50) {
                break@outerLoop
            }
        }
    }
    
    // Label with continue
    loop@ for (i in 1..10) {
        for (j in 1..10) {
            if (j == 5) continue@loop
            println("$i:$j")
        }
    }
    
    // Return statement
    val checkValue = returnIfNegative(x)
    println(checkValue)
}

fun returnIfNegative(value: Int): String {
    if (value < 0) {
        return "Negative"
    }
    return "Non-negative"
}

// Extension functions with control flow
fun String.countVowels(): Int {
    var count = 0
    for (char in this) {
        when (char.lowercaseChar()) {
            'a', 'e', 'i', 'o', 'u' -> count++
        }
    }
    return count
}
