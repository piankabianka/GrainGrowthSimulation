
//CANVAS
const canvas=document.querySelector('canvas');
canvas.width=window.innerWidth;
canvas.height=window.innerHeight-document.querySelector('#navigation').offsetHeight;
const c=canvas.getContext('2d');


const submitButton=document.querySelector('#submit');
const stepButton=document.querySelector('#step');
const removeButton=document.querySelector('#remove');

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

let borderConditionValue=undefined;
let nghbValue=undefined;

let bc=undefined;
let nghb=undefined;

let dataToDisplay=undefined;
let counter=0;

const temperatureOption=document.querySelector("#temperature-option");
const siteNav=document.querySelector('#site-navigation');

let temperatureInfluence=false;
const t1=document.querySelector('#t1');
const t2=document.querySelector('#t2');
const t3=document.querySelector('#t3');
const t4=document.querySelector('#t4');
let temp1;
let temp2;
let temp3;
let temp4;
let polynomialTypeValue=undefined;
let polynomialType=undefined;

function drawGrid(){
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
}

function drawCells(dataToDisplay){
    let color="";
    let colorArray=[];

    for(let c of dataToDisplay){
        if(c===";"){
            colorArray.push(color);
            color="";
        }
        else if(c==="\n"){
            console.log();
        }
        else{
            color+=c;
        }
    }

    let singleColor="";
    

    for(let i=startPoint+1; i<endPointY; i+=cellSize){
        for(let j=startPoint+1; j<endPointX; j+=cellSize){
            singleColor="rgb("+colorArray[counter]+")";
            c.fillStyle=singleColor;
            //c.fillRect(j,i,cellSize-1, cellSize-1);
            c.fillRect(j,i,cellSize, cellSize);
            counter++;
        }
    }
}

function saveDataToFile(){
    var fs=require('fs');
    const path = require('path');
    let string="";
    string+=elementsXValue+"\n"+elementsYValue+"\n"+grainsNumber+"\n"+kT+"\n"+bc+"\n"+nghb;

  
    string+="\n"+temp1+"\n"+temp2+"\n"+temp3+"\n"+temp4+"\n"+polynomialType;


    fs.writeFileSync("./data.txt",string, 'utf8', function(err){
        if(err){
            console.log(err);
        }
    })

    return path.resolve('./data.txt');


}

function readDataFromFile(){
    var fs=require('fs');
    return fs.readFileSync('./calculatedData.csv','utf8');
}

//SUBMIT DATA
submitButton.addEventListener('click', function(e){
    e.preventDefault();

    elementsXValue=elementsX.querySelector('input[type="text"]').value;
    elementsYValue=elementsY.querySelector('input[type="text"]').value;
    endPointX=cellSize*elementsXValue;
    endPointY=cellSize*elementsYValue;
    grainsNumber=grains.querySelector('input[type="text"]').value;
    kT=kTParameter.querySelector('input[type="text"]').value;
    borderConditionValue=document.querySelector('#border-conditions option:checked').value;
    nghbValue=document.querySelector('#neighbourhood-type option:checked').value;
    polynomialTypeValue=document.querySelector('#polynomial option:checked').value;
    
    if(borderConditionValue=='Periodic'){
        bc=1;
    } else if(borderConditionValue=='Absorbable'){
        bc=2;
    }

    if(nghbValue=='Neumann'){
        nghb=1;
    } else if(nghbValue=='Moore'){
        nghb=2;
    }

    

    if(temperatureInfluence){
        temp1=t1.querySelector('input[type="text"]').value;
        temp2=t2.querySelector('input[type="text"]').value;
        temp3=t3.querySelector('input[type="text"]').value;
        temp4=t4.querySelector('input[type="text"]').value;   
        if(polynomialTypeValue=='linear'){
            polynomialType=1;
        }  else if(polynomialTypeValue=='second'){
            polynomialType=2;
        } else{
            polynomialType=3;
        }   
    }else{
        temp1=-1;
        temp2=-1;
        temp3=-1;
        temp4=-1;
        polynomialType=-1;
    }
    

    const path = saveDataToFile();

    const { execFile } = require('child_process');


    execFile('../ProgramCalculations/Release/ProgramCalculations.exe',[path], (error, stdout, stderr)=>{
        
        drawGrid();
        
        dataToDisplay=readDataFromFile();
    
        drawCells(dataToDisplay);
    })

    

})

stepButton.addEventListener('click', function(e){
    e.preventDefault();

    drawCells(dataToDisplay);
})

removeButton.addEventListener('click', function(e){

    e.preventDefault();

    elementsX.querySelector('input[type="text"]').value="";
    elementsY.querySelector('input[type="text"]').value="";
    grains.querySelector('input[type="text"]').value="";
    kTParameter.querySelector('input[type="text"]').value="";

    const fs = require('fs')

    const path = './calculatedData.csv'

    try {
    fs.unlinkSync(path)
    //file removed
    } catch(err) {
    console.error(err)
    }

    c.clearRect(0, 0, canvas.width, canvas.height);
})

temperatureOption.addEventListener('click', function(e){
    
    if(e.target.checked){
        siteNav.classList.add("show");
        temperatureInfluence=true;
    }
    else{
        siteNav.classList.remove("show");
        temperatureInfluence=false;
    }

})