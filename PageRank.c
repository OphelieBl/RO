
#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include "edgelist.h"

struct website {
    unsigned long int id;
    long double probability;
};


int compareProba (const void * a, const void * b)
{
    if ((*(struct website*)b).probability - (*(struct website*)a).probability >0) {
        return 1;
    } else if ((*(struct website*)b).probability - (*(struct website*)a).probability <0){
        return -1;
    } else {
        return 0;
    }
}

long double *PageRank(edgelist * g, float alpha, int nb_iter){
    unsigned long int nbNodes = g->n;
    unsigned long int nbEdges = g->e;
    unsigned int * dout = malloc((nbNodes)*sizeof(unsigned int));
    unsigned int * din = malloc((nbNodes)*sizeof(unsigned int));
    long double * proba = malloc((nbNodes)*sizeof(long double));
    for (unsigned long int i = 0; i < nbNodes; i++)
    {
        dout[i]=0;
        din[i]=0;
    }
    // boucle din et dout puis calcul n réel et ensuite boucle sur les liens ABS pour convergence ?
    for (unsigned long int i = 0; i < nbEdges; i++){
        dout[g->edges[i].s]+=1;
        din[g->edges[i].t]+=1;
    }
    unsigned long int nbLinkedNodes = 0;
    for (unsigned long int i = 0; i < nbNodes; i++)
    {
        // si au moins un lien entre ou sort du noeud
        if(dout[i]+din[i]!=0){
            nbLinkedNodes+=1;
        } else {
            proba[i]=0;
        }
    }
    printf("there are %lu connected Nodes in this graph \n", nbLinkedNodes);
    for (unsigned long int i = 0; i < nbNodes; i++){
        if(dout[i]+din[i]!=0){
            proba[i] = (long double) 1 / nbLinkedNodes;
        }
    } 

    for (int i = 0; i < nb_iter; i++){
        long double * pt = malloc((nbNodes)*sizeof(long double));
        for (unsigned long int i = 0; i < nbNodes; i++)
        {
            pt[i]=0;
        }
        float somme = 0;
        for (int j = 0; j < nbEdges; j++){
            pt[g->edges[j].t] += (1-alpha)/dout[g->edges[j].s]*proba[g->edges[j].s];
            somme += (1-alpha)/dout[g->edges[j].s]*proba[g->edges[j].s];
        }
        // alpha/nbLinkedNodes is added nbLinkedNodes times
        somme += alpha;
        for (unsigned long int noeud = 0; noeud < nbNodes; noeud ++){
            if (dout[noeud]+din[noeud]!=0){
                proba[noeud] = pt[noeud] + alpha/nbLinkedNodes + (1-somme)/nbLinkedNodes;
            }
        }
        free(pt);
    }
    //écriture dans un fichier pour tracer
    /*FILE* fichier = NULL;
 
    fichier = fopen("alpha2.txt", "w");
 
    if (fichier != NULL)
    {
        for (unsigned long int i = 0; i < nbNodes; i++)
        {
            // si au moins un lien entre ou sort du noeud
            if(dout[i]+din[i]>0.5){
                fprintf(fichier, "%.10LF\n", proba[i]);
            }
        }
        fclose(fichier);
    }*/
    // récupérer les probas des plus importants
    struct website * webSites = (struct website *)malloc((nbLinkedNodes)*sizeof(struct website));
    int j = 0;
    for (unsigned long int i = 0; i < g->n; i++)
    {
        if(dout[i]+din[i]>0.5){
            webSites[j].id=i;
            webSites[j].probability=proba[i];
            j=j+1;
        }
    }
    // tri de la liste
    qsort(webSites, nbLinkedNodes, sizeof( struct website), compareProba);
    printf("minProba %LF %lu\n", webSites[0].probability, webSites[0].id);
    printf("minProba %LF %lu\n", webSites[1].probability, webSites[1].id);
    printf("minProba %LF %lu\n", webSites[2].probability, webSites[2].id);
    printf("minProba %LF %lu\n", webSites[3].probability, webSites[3].id);
    printf("minProba %LF %lu\n", webSites[4].probability, webSites[4].id);
    printf("maxProba %LF %lu\n", webSites[nbLinkedNodes - 1].probability, webSites[nbLinkedNodes - 1].id);
    printf("maxProba %LF %lu\n", webSites[nbLinkedNodes - 2].probability, webSites[nbLinkedNodes - 2].id);
    printf("maxProba %LF %lu\n", webSites[nbLinkedNodes - 3].probability, webSites[nbLinkedNodes - 3].id);
    printf("maxProba %LF %lu\n", webSites[nbLinkedNodes - 4].probability, webSites[nbLinkedNodes - 4].id);
    printf("maxProba %.10LF %lu\n", webSites[nbLinkedNodes - 5].probability, webSites[nbLinkedNodes - 5].id);

    free(webSites);
    free(dout);
    free(din);
    return proba;  
}

//différent de 0 plus grand que epsilon dout + din >0.1

int main(int argc,char** argv){
	edgelist* g;
    float alpha = 0.15;
    int nb_iter = 20;
	time_t t1,t2;

	t1=time(NULL);

	printf("Reading edgelist from file %s\n",argv[1]);
	g=readedgelist(argv[1]);


	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);
    long double * proba = PageRank( g, alpha, nb_iter);

	free_edgelist(g);
    free(proba);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}

