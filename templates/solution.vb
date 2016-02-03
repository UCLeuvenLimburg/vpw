Imports System.IO

Module Module1

    Private stdin As TextReader = System.Console.In
    Private stdout As TextWriter = System.Console.Out

    Sub Main()
        Dim aantal As Integer = CInt(stdin.ReadLine)
        For i As Integer = 0 To aantal - 1
            Dim lijn() As String = stdin.ReadLine.Split(" ")
            Dim k As Integer = CInt(lijn(0))
            stdout.WriteLine(lijn(1).Substring(k - 1, 1))
        Next
    End Sub

End Module