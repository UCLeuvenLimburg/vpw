import Control.Monad
    

scores = replicate 4 25 ++ replicate 4 100 ++ replicate 4 500 ++ repeat 1000
score = sum . flip take scores

main = do n <- read `fmap` getLine
          forM [1..n] processCase
    where
      processCase index = do getLine
                             jumps <- (map read . words) `fmap` getLine
                             let solution = sum $ map score jumps
                             putStrLn $ show index ++ " " ++ show solution
          
