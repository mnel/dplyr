\name{manip_dt}
\alias{arrange.data.table}
\alias{filter.data.table}
\alias{manip_dt}
\alias{mutate.data.table}
\alias{select.data.table}
\alias{summarise.data.table}
\title{Data manipulation for data tables.}
\usage{
  \method{filter}{data.table} (.data, ...,
    .env = parent.frame())

  \method{summarise}{data.table} (.data, ...)

  \method{mutate}{data.table} (.data, ..., inplace = FALSE)

  \method{arrange}{data.table} (.data, ...)

  \method{select}{data.table} (.data, ...)
}
\arguments{
  \item{.data}{a data table}

  \item{...}{variables interpreted in the context of
  \code{.data}}

  \item{inplace}{if \code{FALSE} (the default) the data
  frame will be copied prior to modification to avoid
  changes propagating via reference.}

  \item{.env}{The environment in which to evaluate
  arguments not included in the data. The default should
  suffice for ordinary usage.}
}
\description{
  Data manipulation for data tables.
}
\examples{
if (require("data.table")) {
# If you start with a data table, you end up with a data table
hflights <- as.data.table(hflights)
filter(hflights, Month == 1, DayofMonth == 1, Dest == "DFW")
head(select(hflights, Year:DayOfWeek))
summarise(hflights, delay = mean(ArrDelay, na.rm = TRUE), n = length(ArrDelay))
head(mutate(hflights, gained = ArrDelay - DepDelay))
head(arrange(hflights, Dest, desc(ArrDelay)))

# If you start with a tbl, you end up with a tbl
hflights2 <- as.tbl(hflights)
filter(hflights2, Month == 1, DayofMonth == 1, Dest == "DFW")
head(select(hflights2, Year:DayOfWeek))
summarise(hflights2, delay = mean(ArrDelay, na.rm = TRUE), n = length(ArrDelay))
head(mutate(hflights2, gained = ArrDelay - DepDelay))
head(arrange(hflights2, Dest, desc(ArrDelay)))
}
}

