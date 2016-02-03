object Main extends App {
  
  def doeEenLijn(s : String) : Char = {
    val gesplitst = s.split(" ")
    return gesplitst(1).charAt(gesplitst(0).toInt - 1)
  }
    
  val aantal = readLine().toInt      
  for (i <- 1 to aantal) {
    println(doeEenLijn(readLine()))
  }
  
}