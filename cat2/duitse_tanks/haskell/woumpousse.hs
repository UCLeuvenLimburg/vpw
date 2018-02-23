import Control.Monad
    

next :: IO Int
next = read `fmap` getLine

readNumbers :: IO [Int]
readNumbers = do n <- next
                 if n < 0
                 then return []
                 else do ns <- readNumbers
                         return (n : ns)

solve :: Int -> IO ()                                
solve index = do ns <- readNumbers
                 let m = maximum ns
                 let n = length ns
                 let r = round( (fromIntegral ((n + 1) * m)) / (fromIntegral n) + 0.001 ) - 1
                 putStrLn $ show index ++ " " ++ show r
                                

main = do n <- next
          forM_ [1..n] solve

