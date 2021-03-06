const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const FaviconsWebpackPlugin = require("favicons-webpack-plugin");
const outputDir = path.join(__dirname, "build/");

const isProd = process.env.NODE_ENV === "production";
const Dotenv = require("dotenv-webpack");

const cssRegex = /\.css$/;

module.exports = {
  entry: "./src/Index.bs.js",
  mode: isProd ? "production" : "development",
  output: {
    path: outputDir,
    publicPath: "/",
    filename: "Index.js",
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "src/index.html",
      favicon: "src/favicon.ico",
      inject: true,
    }),
    new FaviconsWebpackPlugin({
      favicons: {
        appName: "Relogify",
        appDescription:
          "Relogify is a web application for collecting and analyzing sports statistics.",
        developerName: "Relogify AB",
        icons: {
          favicons: false,
        },
      },
    }),
    new Dotenv({ systemvars: true }),
  ],
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true,
  },
  module: {
    rules: [
      {
        test: cssRegex,
        use: ["style-loader", "css-loader"],
      },
    ],
  },
};
