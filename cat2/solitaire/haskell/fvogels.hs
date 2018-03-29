import Control.Monad
import Data.List


rightJumps :: [Bool] -> [[Bool]]
--------------------------------
rightJumps [] = []
rightJumps (True:True:False:xs) = (False:False:True:xs) : map (True:) (rightJumps $ True:False:xs)
rightJumps (x:xs)               = map (x:) (rightJumps xs)


leftJumps :: [Bool] -> [[Bool]]
-------------------------------
leftJumps = map reverse . rightJumps . reverse


jumps :: [Bool] -> [[Bool]]
---------------------------
jumps bs = rightJumps bs ++ leftJumps bs


nest :: (a -> a) -> Int -> a -> a
---------------------------------
nest f 0 = id
nest f n = f . nest f (n - 1)


reduce :: [Bool] -> [[Bool]]
----------------------------
reduce bs = nest (nub . concatMap jumps) (count bs - 1) [bs]


count :: [Bool] -> Int
----------------------
count = sum . map (\x -> if x then 1 else 0)


firstIndex :: [Bool] -> Int
---------------------------
firstIndex (True:_) = 0
firstIndex (False:xs) = 1 + firstIndex xs


safeMin :: Ord a => [a] -> Maybe a
----------------------------------
safeMin [] = Nothing
safeMin xs = Just $ minimum xs


solve :: [Bool] -> Maybe Int
----------------------------
solve = safeMin . map firstIndex . filter ((== 1) . count) . reduce



main :: IO ()
-------------
main = do n <- read `fmap` getLine
          forM_ [1..n] aux
  where
    aux :: Int -> IO ()
    aux idx = do n:ns <- (map read . words) `fmap` getLine
                 let bs = map (== 1) ns
                 case solve bs of
                   Nothing -> putStrLn $ show idx ++ " ONMOGELIJK"
                   Just k -> putStrLn $ show idx ++ " " ++ show (k + 1)
