
//CANVAS
const canvas=document.querySelector('canvas');
canvas.width=window.innerWidth;
canvas.height=window.innerHeight-document.querySelector('#navigation').offsetHeight;
const c=canvas.getContext('2d');


const submitButton=document.querySelector('#submit');

const elementsX=document.querySelector('#nodesX');
let elementsXValue=undefined;

const elementsY=document.querySelector('#nodesY');
let elementsYValue=undefined;

const cellSize=5;
const startPoint=0;
let endPointX=undefined
let endPointY=undefined;

const grains=document.querySelector('#grainsNumber');
let grainsNumber=undefined;

const kTParameter=document.querySelector('#kTParameter');
let kT=undefined;

let parameters={};


//SUBMIT DATA
submitButton.addEventListener('click', function(e){
    e.preventDefault();

    elementsXValue=elementsX.querySelector('input[type="text"]').value;
    elementsYValue=elementsY.querySelector('input[type="text"]').value;
    endPointX=cellSize*elementsXValue;
    endPointY=cellSize*elementsYValue;
    grainsNumber=grains.querySelector('input[type="text"]').value;
    kT=kTParameter.querySelector('input[type="text"]').value;

    var fs=require('fs');
    let string="";
    string+=elementsXValue+"\n"+elementsYValue+"\n"+grainsNumber+"\n"+kT;
    fs.writeFileSync("C:/Users/Bianka/Desktop/Moja nauka/Materiały do inżynierki/Kody/GrainGrowthSimulation/ProgramCalculations/Debug/data.txt",string, 'utf8', function(err){
        if(err){
            console.log(err);
        }
    })
    
    for(let i=0; i<=elementsXValue; i++){
        c.beginPath();
        c.moveTo(i*cellSize, startPoint);
        c.lineTo(i*cellSize, endPointY);
        c.strokeStyle="#C7D4CF";
        c.stroke();
    }
    
    for(let i=0; i<=elementsYValue; i++){
        c.beginPath();
        c.moveTo(startPoint, i*cellSize);
        c.lineTo(endPointX, i*cellSize);
        c.strokeStyle="#C7D4CF";
        c.stroke();

    }
    
   
    const dataToDisplay=fs.readFileSync('C:/Users/Bianka/Desktop/Moja nauka/Materiały do inżynierki/Kody/GrainGrowthSimulation/ProgramCalculations/Debug/calculatedData.csv','utf8');
    let color="";
    let colorArray=[];

    for(let c of dataToDisplay){
        if(c==="\n"){
            colorArray.push(color);
            color="";
        }
        else{
            color+=c;
        }
    }

    console.log(colorArray);

    let singleColor="";
    let counter=0;

    for(let i=startPoint+1; i<endPointY; i+=cellSize){
        for(let j=startPoint+1; j<endPointX; j+=cellSize){
            singleColor="rgb("+colorArray[counter]+")";
            c.fillStyle=singleColor;
            c.fillRect(j,i,cellSize-1, cellSize-1);
            counter++;
        }
    }


})

    