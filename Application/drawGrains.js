//DATA- connecting cpp script
const data = require('./drawGrid.js');
//module.exports = require("bindings")("addon");
const addon = require('./build/Release/addon.node');

//DATA- variables
const stepButton=document.querySelector('#step');

const context=data.getCanvas().c;

let grainsTable=[];
let grainsTableInitialised=false;

function initialiseGrainsTable(){
    console.log('inicjalizacja tablicy');

    for(let i=0; i<data.getData().nodesYValue-1; i++){
        grainsTable[i]=[];
    }

    for(let i=0; i<data.getData().nodesYValue-1; i++){
        for(let j=0; j<data.getData().nodesXValue-1; j++){
            grainsTable[i][j]='white';
            /*if(j%2!=0){
                grainsTable[i][j]='blue';
            }
            else{
                grainsTable[i][j]='red';
            }*/
        }
    }

    console.log(grainsTable);
    grainsTableInitialised=true;
}

function setColor(i,j){
    return(grainsTable[i][j]);
}

function drawGrains(){

    if(!grainsTableInitialised)
     initialiseGrainsTable();
    else{
        console.log(addon.IsPrime(3));
    }


    let c1=0;
    let c2=0;   
    
    for(let i=data.getData().startPoint+1; i<data.getData().endPointY; i+=data.getData().cellSize){
        for(let j=data.getData().startPoint+1; j<data.getData().endPointX; j+=data.getData().cellSize){
            context.fillStyle=setColor(c1,c2);
            context.fillRect(j,i,cellSize-1, cellSize-1);
            c2++;
        }
        c1++;
        c2=0;
    }

    //console.log(addon.IsPrime(3));
}

stepButton.addEventListener('click', function(e){
    //console.log(data.getData());
    
    drawGrains();
})