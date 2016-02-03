module Main where

import System.IO
import Control.Monad (liftM)


transform :: [String] -> [Char]
transform [] = []
transform (cs:css) =
  let (i:s:_) = words cs
  in (s !! (read i - 1)):transform css


main :: IO ()
main = do
  n <- read `liftM` getLine :: IO Int
  lss <- lines `liftM` getContents

  let cases = take n lss
      chars = transform cases

  putStr $ unlines $ map (\c -> [c]) chars
      