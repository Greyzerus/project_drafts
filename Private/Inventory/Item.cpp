// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Item.h"

FItem::FItem() : 
	ItemRef(nullptr), 
	ItemCount(0) 
{}

FItem::FItem(APickUp* ItemRef, int ItemCount) :
	ItemRef(ItemRef), 
	ItemCount(ItemCount) 
{}

void FItem::IncreaseCount(int count) 
{
	if (ItemRef == nullptr)		return;
	else						ItemCount += count;
}

bool FItem::operator== (FItem other)
{ return *this->ItemRef == *other.ItemRef; }

