const submitButton=document.querySelector('#submit');
const elementsX=document.querySelector('#nodesX');
const elementsY=document.querySelector('#nodesY');
const grains=document.querySelector('#grainsNumber');
const kTParameter=document.querySelector('#kTParameter');

let elementsXValue=undefined;
let elementsYValue=undefined;
let grainsNumber=undefined;
let kT=undefined;

submitButton.addEventListener('click', function(e){
    e.preventDefault();
    elementsXValue=elementsX.querySelector('input[type="text"]').value;
    elementsYValue=elementsY.querySelector('input[type="text"]').value;
    grainsNumber=grains.querySelector('input[type="text"]').value;
    kt=kTParameter.querySelector('input[type="text"]').value;


    var fs=require('fs');

    


    
    
});

const getData = () => {
    return colorArray;
  };
  
  module.exports.getData = getData;