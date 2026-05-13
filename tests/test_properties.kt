package com.example

class Account {
    var balance: Double = 0.0
    val accountNumber: String = "12345"
    
    var amount: Int = 0
        get() = field * 2
        set(value) {
            if (value > 0) {
                field = value
            }
        }
    
    val isActive: Boolean by lazy {
        balance > 0
    }
    
    val type: String get() = "Account"
    
    companion object {
        const val INITIAL_BALANCE = 1000.0
        var totalAccounts = 0
    }
}

val globalValue = 100
var globalMutable = 200

val list: MutableList<String> = mutableListOf("a", "b", "c")

val (x, y) = Pair(1, 2)

var (name, age): Pair<String, Int> = Pair("John", 30)

enum class Color(val hex: String) {
    RED("#FF0000"),
    GREEN("#00FF00"),
    BLUE("#0000FF");
    
    val isLight: Boolean
        get() = this == RED
}

data class Point(val x: Int, val y: Int)

sealed class Result<out T> {
    data class Success<T>(val data: T) : Result<T>()
    data class Error(val message: String) : Result<Nothing>()
}
