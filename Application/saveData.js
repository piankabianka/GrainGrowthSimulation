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

    let string="";
    string+=elementsXValue+"\n"+elementsYValue+"\n"+grainsNumber+"\n"+kt;
    fs.writeFileSync("C:/Users/Bianka/Desktop/Moja nauka/Materiały do inżynierki/Kody/GrainGrowthSimulation/ProgramCalculations/Debug/data.txt",string, 'utf8', function(err){
        if(err){
            console.log(err);
        }
    })
});