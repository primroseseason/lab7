//
//  linktable.c
//  lab7
//
//  Created by 高旭 on 2017/11/2.
//  Copyright © 2017年 高旭. All rights reserved.
//

#include"linktable.h"
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
/*LinkTable Type*/
typedef struct LinkTable
{
    tLinkTableNode *head;
    tLinkTableNode *tail;
    int nodeCount;
    pthread_mutex_t mutex;
}tLinkTable;
/*Create a LinkTable*/
tLinkTable* CreateLinkTable()
{
    tLinkTable* pLinkTable = (tLinkTable*)malloc(sizeof(tLinkTable));
    if(pLinkTable==NULL)
    {
        return NULL;
    }
    pLinkTable->head = NULL;
    pLinkTable->tail =NULL;
    pLinkTable->nodeCount = 0;
    pthread_mutex_init(&(pLinkTable->mutex), NULL);
    return pLinkTable;
}
/*Delete a LinkTable*/
int DeleteLinkTable(tLinkTable* pLinkTable)
{
    if(pLinkTable==NULL)
    {
        return  FAILURE;
    }
    while(pLinkTable->head!=NULL)
    {
        tLinkTableNode *tmp = pLinkTable->head;
        pthread_mutex_lock(&(pLinkTable->mutex));
        pLinkTable->head = pLinkTable->head->next;
        pLinkTable->nodeCount -= 1 ;
        pthread_mutex_unlock(&(pLinkTable->mutex));
        free(tmp);
    }
    pLinkTable->head = NULL;
    pLinkTable->tail=NULL;
    pLinkTable->nodeCount = 0;
    pthread_mutex_destroy(&(pLinkTable->mutex));
    free(pLinkTable);
    return SUCCESS;
}
/*Add a LinkTableNode*/
int AddLinkTableNode(tLinkTable* pLinkTable, tLinkTableNode* pNode)
{
    if(pLinkTable==NULL||pNode==NULL)
    {
        return  FAILURE;
    }
    pNode->next = NULL;
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->head ==  NULL)
    {
        pLinkTable->head = pNode;
    }
    if(pLinkTable->tail == NULL)
    {
        pLinkTable->tail = pNode;
    }
    else
    {
        pLinkTable->tail->next = pNode;
        pLinkTable->tail = pNode;
    }
    pLinkTable->nodeCount++;
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return SUCCESS;
}
int DelLinkTableNode(tLinkTable* pLinkTable, tLinkTableNode* pNode)
{
    if(pLinkTable==NULL||pNode==NULL)
    {
        return  FAILURE;
    }
    pthread_mutex_lock(&(pLinkTable->mutex));
    if(pLinkTable->head == pNode)
    {
        pLinkTable->head = pLinkTable->head->next;
        pLinkTable->nodeCount--;
        if(pLinkTable->nodeCount== 0)
        {
            pLinkTable->tail = NULL;
        }
        pthread_mutex_unlock(&(pLinkTable->mutex));
        return SUCCESS;
    }
    tLinkTableNode *tmp = pLinkTable->head;
    while(tmp!=NULL)
    {
        if(tmp->next == pNode)
        {
            tmp->next = pNode->next->next;
            pLinkTable->nodeCount--;
            if(pLinkTable->nodeCount == 0)
            {
                pLinkTable->tail = NULL;
            }
            pthread_mutex_unlock(&(pLinkTable->mutex));
            return SUCCESS;
        }
        tmp = tmp->next;
    }
    pthread_mutex_unlock(&(pLinkTable->mutex));
    return FAILURE;
}
/*Search a LinkTableNode from LinkTable*/
tLinkTableNode* SearchLinkTableNode(tLinkTable* pLinkTable, int Condition(tLinkTableNode* pNode,void* args),void* args)
{
    if(pLinkTable==NULL||Condition==NULL)
    {
        return NULL;
    }
    tLinkTableNode*pNode=pLinkTable->head;
    //while(pNode!=pLinkTable->tail)
    while(pNode!=NULL)
    {
        if(Condition(pNode,args)==SUCCESS)
        {
            return pNode;
        }
        pNode=pNode->next;
    }
    return NULL;
}
/*get LinkTableHead*/
tLinkTableNode* GetLinkTableHead(tLinkTable* pLinkTable)
{
    if(pLinkTable == NULL)
    {
        return NULL;
    }
    return pLinkTable->head;
}
/*get NextLinkTableNode*/
tLinkTableNode* GetNextLinkTableNode(tLinkTable* pLinkTable, tLinkTableNode* pNode)
{
    if(pLinkTable == NULL || pNode == NULL)
        return NULL;
    
    tLinkTableNode *tmp  =  pLinkTable->head;
    while(tmp!=NULL)
    {
        if(tmp == pNode)
        {
            return tmp->next;
        }
        tmp = tmp->next;
    }
    return NULL;
}

