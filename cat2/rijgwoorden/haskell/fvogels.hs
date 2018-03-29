import Control.Monad
import Data.List
import Data.Function
import Debug.Trace


extracts :: [a] -> [(a, [a])]
-----------------------------
extracts []     = []
extracts (x:xs) = (x, xs) : [ (y, x:ys) | (y, ys) <- extracts xs ]


maxima :: (a -> a -> Ordering) -> [a] -> [a]
--------------------------------------------
maxima cmp []           = []
maxima cmp (x:xs)       = aux [x] xs
    where
      aux acc []        = acc
      aux (x:xs) (y:ys) = case cmp x y of
                            LT -> aux [y] ys
                            EQ -> aux (y:x:xs) ys
                            GT -> aux (x:xs) ys
             

solve :: [String] -> [String]
-----------------------------
solve words = longest $ concatMap (aux [] words) [ 'a' .. 'z' ]
    where
      aux acc words z = case filter (\(w, _) -> head w == z) (extracts words) of
                          []     -> if length acc > 1 then [ concat $ reverse acc ] else []
                          words' -> concat [ aux (w : acc) ws (last w)
                                           | (w, ws) <- words'
                                           ]

      longest = maxima (compare `on` length)


main :: IO ()
-------------
main = do input <- lines `fmap` getContents
          let n = read $ head input
          forM_ (zip [1..] (take n $ tail input)) (uncurry aux)
    where
      aux idx input = putStrLn $ show idx ++ " " ++ case solve $ tail $ words input of
                                                      [] -> "geen oplossing"
                                                      xs -> unwords (sort xs)
