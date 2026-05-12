package com.example

fun add(a: Int, b: Int): Int = a + b

fun greet(name: String, greeting: String = "Hello"): String {
    return "$greeting, $name!"
}

fun fibonacci(n: Int): Int {
    return if (n <= 1) n else fibonacci(n - 1) + fibonacci(n - 2)
}

inline fun <T> executeBlock(block: () -> T): T {
    return block()
}

fun List<String>.printAll() {
    forEach { println(it) }
}

suspend fun asyncOperation(x: Int): Int {
    return x * 2
}

operator fun String.times(count: Int): String {
    var result = ""
    repeat(count) { result += this }
    return result
}

infix fun Int.power(exponent: Int): Int {
    var result = 1
    repeat(exponent) { result *= this }
    return result
}
