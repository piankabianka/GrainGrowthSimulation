
//CANVAS
const canvas=document.querySelector('canvas');
const c=canvas.getContext('2d');

//BUTTONS
const submitButton=document.querySelector('#submit');
const stepButton=document.querySelector('#step');
const saveImageButton=document.querySelector('#link');
const removeButton=document.querySelector('#remove');

//VALUES
const elementsX=document.querySelector('#nodesX');
const elementsY=document.querySelector('#nodesY');
const grains=document.querySelector('#grainsNumber');
const kTParameter=document.querySelector('#kTParameter');
const mc=document.querySelector('#mcSteps');
const temperatureOption=document.querySelector("#temperature-option");
const siteNav=document.querySelector('#site-navigation');
const t1=document.querySelector('#t1');
const t2=document.querySelector('#t2');
const t3=document.querySelector('#t3');
const t4=document.querySelector('#t4');

//PARAMETERS
const cellSize=3;
const startPoint=0;
let endPointX=undefined
let endPointY=undefined;
let dataToDisplay=undefined;
let counter=0;
let temperatureInfluence=false;


function drawGrid(elementsXValue, elementsYValue){

    canvas.width=elementsXValue*cellSize;
    canvas.height=elementsYValue*cellSize;
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
    

    for(let i=startPoint; i<endPointY; i+=cellSize){
        for(let j=startPoint; j<endPointX; j+=cellSize){
            singleColor="rgb("+colorArray[counter]+")";
            c.fillStyle=singleColor;
            //c.fillRect(j,i,cellSize-1, cellSize-1);
            c.fillRect(j,i,cellSize, cellSize);
            counter++;
        }
    }
}

function saveDataToFile(elementsXValue, elementsYValue, grainsNumber, kT, mcValue, bc, nghb, polynomialType, temp1, temp2,temp3, temp4){
    console.log("Saving data to file!");
    var fs=require('fs');
    const path = require('path');
    let string="";
    string+=elementsXValue+"\n"+elementsYValue+"\n"+grainsNumber+"\n"+kT+"\n"+mcValue+"\n"+bc+"\n"+nghb;

  
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
function getData(elementsXValue, elementsYValue){
    
   endPointX=cellSize*elementsXValue;
   endPointY=cellSize*elementsYValue;
   let grainsNumber=grains.querySelector('input[type="text"]').value;
   let kT=kTParameter.querySelector('input[type="text"]').value;
   let mcValue=mc.querySelector('input[type="text"]').value;
   let borderConditionValue=document.querySelector('#border-conditions option:checked').value;
   let nghbValue=document.querySelector('#neighbourhood-type option:checked').value;
   let polynomialTypeValue=document.querySelector('#polynomial option:checked').value;
    
   let bc;
    if(borderConditionValue=='Periodic'){
        bc=1;
    } else if(borderConditionValue=='Absorbable'){
        bc=2;
    }

    let nghb;
    if(nghbValue=='Neumann'){
        nghb=1;
    } else if(nghbValue=='Moore'){
        nghb=2;
    }

    let  polynomialType=0;
    let temp1;
    let temp2;
    let temp3;
    let temp4;

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
    
    return saveDataToFile(elementsXValue, elementsYValue, grainsNumber, kT,mcValue, bc, nghb, polynomialType, temp1, temp2,temp3, temp4);
}

//SUBMIT DATA
submitButton.addEventListener('click', function(e){
    e.preventDefault();
    let elementsXValue=elementsX.querySelector('input[type="text"]').value;
    let elementsYValue=elementsY.querySelector('input[type="text"]').value;

    const path = getData(elementsXValue, elementsYValue);

    const { execFile } = require('child_process');


    execFile('../ProgramCalculations/Release/ProgramCalculations.exe',[path], (error, stdout, stderr)=>{
        stepButton.classList.remove("do-not-show-button"); 
        saveImageButton.classList.remove("do-not-show-button");
        removeButton.classList.remove("do-not-show-button"); 

        stepButton.classList.add("show-button"); 
        saveImageButton.classList.add("show-button");
        removeButton.classList.add("show-button");       
        drawGrid(elementsXValue, elementsYValue);
        
        dataToDisplay=readDataFromFile();
    
        drawCells(dataToDisplay);
    })
})

let number=0;

stepButton.addEventListener('click', function(e){
    e.preventDefault();
    number+=50;
    
    document.getElementById('counter').innerHTML ="krok "+number;
    drawCells(dataToDisplay);
    
})

removeButton.addEventListener('click', function(e){

    const fs = require('fs');
    const path = './calculatedData.csv';

    try {
        fs.unlinkSync(path)
        
        //file removed
        } catch(err) {
        console.error("No file to delete");
        }

        location.reload();  

    
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

saveImageButton.addEventListener('click', function(e){
    e.preventDefault();
    let link = document.createElement('a');
    link.download = "picture.png";
    link.href = canvas.toDataURL("image/png").replace("image/png", "image/octet-stream");
    link.click();
})